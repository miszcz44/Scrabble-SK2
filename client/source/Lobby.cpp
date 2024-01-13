//
// Created by erykb on 30.12.2023.
//
#include <Lobby.h>

Lobby::Lobby(RenderWindow &window) : window(window), roomToDraw(window){
    if (!font.loadFromFile("../assets/Fonts/Arialn.ttf")) {
        cout << "Error loading font" << endl;
    }
    Text text;
    roomList.push_back(text);
    roomList[0].setFont(font);
    roomList[0].setFillColor(sf::Color::Red);
    roomList[0].setString("Create lobby");
    roomList[0].setCharacterSize(70);
    roomList[0].setPosition(300, 50);
    lobbySelected = 0;
    roomsCounter = 1;
    enterRoomFlag = false;
    flag = false;
}

Lobby::~Lobby() {

}

void Lobby::createRoom() {
    write(client.sock, "@", 1);
    WaitingRoom waitingRoom(window);
    int a = read(client.sock, client.buffer, 20);
    waitingRoom.setName(client.buffer);
    enterRoom(waitingRoom);
}

void Lobby::enterRoom(WaitingRoom room) { // 3:45 31.12.2023 CHUJ W DUPIE
    enterRoomFlag = true;
    while(!room.isGoBackFlag() && enterRoomFlag) {
        window.clear();
        int res =  room.draw(client);;
        if(res == 0) {
            enterRoomFlag = false;
            break;
        }
        if(res == 2) {
            flag = true;
            enterRoomFlag = false;
            break;
        }
    }
}

bool Lobby::validateNickAvailability(string nick) {
    if(nick == "aaa") {
        return false;
    }
    for(Player player : players) {
        if(nick == player.getNickname()) {
            return false;
        }
    }
    return true;
}

bool Lobby::draw(Client klajent) {
    if(flag) {
        return true;
    }
    client = klajent;
    write(client.sock, "%", 1);
    ssize_t a = read(client.sock, client.buffer, 255);
    if(a > 0) {
        string tmp;
        string name;
        vector<string> names;
        for(int i = 0; i < a; i++) {
            bool flag = 1;
            if(client.buffer[i] == '|') {
                name = tmp;
                tmp.push_back(' ');
                continue;
            }
            if(client.buffer[i] == '.') {
                names.push_back(tmp);
                for(int i = 0; i < roomList.size(); i++) {
                    if(roomList[i].getString().toAnsiString() == tmp || tmp == "") {
                        tmp = "";
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0)
                {
                    continue;
                }
                bool flag2 = true;
                for(WaitingRoom room : rooms) {
                    if(room.getName() == name) {
                        for(int j = 0; j < roomList.size(); j++) {
                            string roomName;
                            bool flag3 = false;
                            for(char ch : roomList[j].getString().toAnsiString()) {
                                if(ch == 'o') {
                                    flag3 = true;
                                }
                                if(ch == ' ' && flag3) {
                                    break;
                                }
                                roomName.push_back(ch);
                            }
                            if(roomName == name) {
                                roomList[j].setString(tmp);
                                break;
                            }
                        }
                        flag2 = false;
                        break;
                    }
                }
                if(flag2) {
                    WaitingRoom room(window);
                    room.setName(name);
                    rooms.push_back(room);
                    Text text;
                    roomList.push_back(text);
                    roomList[roomsCounter].setFont(font);
                    roomList[roomsCounter].setFillColor(sf::Color::Red);
                    roomList[roomsCounter].setString(tmp);
                    roomList[roomsCounter].setCharacterSize(70);
                    roomList[roomsCounter].setPosition(200, 60 * (roomsCounter+2));
                    roomsCounter++;
                }

                tmp = "";
                continue;
            }
            tmp.push_back(client.buffer[i]);
        }
        for(int i = 1; i < roomsCounter; i++) {
            bool flag = false;
            for(string namu : names) {
                if(roomList[i].getString().toAnsiString() == namu) {
                    flag = true;
                    break;
                }
            }
            if(!flag) {
                Vector2f position = roomList[i].getPosition();
                roomList[i] = roomList[roomsCounter-1];
                roomList[i].setPosition(position);
                if(lobbySelected == i) {
                    lobbySelected--;
                }
                roomList.pop_back();
                roomsCounter--;
                break;
            }
        }
    }
    if(!enterRoomFlag) {
        for (const auto & i : roomList) {
            window.draw(i);
        }
        playerInput();
        window.display();
    }
    return false;
}

void Lobby::playerInput() {
    Event event{};

    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if(event.type == Event::KeyReleased) {
            if (event.key.code == Keyboard::Up) {
                moveUp();
                break;
            }
            if (event.key.code == Keyboard::Down) {
                moveDown();
                break;
            }
            if (event.key.code == Keyboard::Return) {
                if(lobbySelected == 0) {
                    createRoom();
                }
                else {
                    for(WaitingRoom room : rooms) {
                        string tmp;
                        bool flag = false;
                        for(char ch : roomList[lobbySelected].getString().toAnsiString()) {
                            if(ch == 'o') {
                                flag = true;
                            }
                            if(ch == ' ' && flag) {
                                break;
                            }
                            tmp.push_back(ch);
                        }
                        if(room.getName() == tmp) {
                            string tmp2;
                            for(char ch : tmp) {
                                if(ch == ' ') {
                                    tmp2.push_back('_');
                                    continue;
                                }
                                tmp2.push_back(ch);
                            }
                            write(client.sock, ("^" + tmp2).c_str(), tmp2.length()+1);
                            enterRoom(room);
                        }
                    }
                }
            }
        }
    }
}

void Lobby::moveUp() {
    if (lobbySelected - 1 >= 0) {
        roomList[lobbySelected].setFillColor(sf::Color::Red);
        lobbySelected--;
        if (lobbySelected == -1) {
            lobbySelected = roomsCounter;
        }
        roomList[lobbySelected].setFillColor(sf::Color::Green);
    }
}

void Lobby::moveDown() {
    if (lobbySelected  <= roomsCounter) {
        roomList[lobbySelected].setFillColor(sf::Color::Red);
        lobbySelected++;
        if (lobbySelected == roomsCounter) {
            lobbySelected = 0;
        }
        roomList[lobbySelected].setFillColor(sf::Color::Green);
    }
}

bool Lobby::isEnterRoomFlag(){
    return enterRoomFlag;
}

WaitingRoom Lobby::getRoomToDraw() {
    return roomToDraw;
}

void Lobby::setEnterRoomFlag(bool enterRoomFlag) {
    Lobby::enterRoomFlag = enterRoomFlag;
}
