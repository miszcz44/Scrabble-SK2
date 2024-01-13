// h
// Created by erykb on 30.12.2023.
//
#include <WaitingRoom.h>

WaitingRoom::WaitingRoom(RenderWindow &window) : window(window) {
    if (!font.loadFromFile("../assets/Fonts/Arialn.ttf")) {
        cout << "Error loading font" << endl;
    }
    goBackFlag = false;
    color = sf::Color::Red;
    playerCounter = 1;
    textflag = true;
    textflag2 = true;
    downKeyClicked = true;
}

int WaitingRoom::draw(Client klajent) {
    if(textflag) {
        Text text;
        playerList.push_back(text);
        playerList[0].setFont(font);
        playerList[0].setFillColor(sf::Color::Red);
        playerList[0].setString(getName() + "\nPress enter to leave");
        playerList[0].setCharacterSize(70);
        playerList[0].setPosition(200, 50);
        textflag = false;
    }
    client = klajent;
    string roomName;
    for(char ch : name) {
        if(ch == ' ') {
            roomName.push_back('_');
            continue;
        }
        roomName.push_back(ch);
    }
    write(client.sock, ('$' + roomName).c_str(), roomName.length()+1);
    ssize_t a = read(client.sock, client.buffer, 255);
    if(a > 0) {
        string tmp;
        char sizeChar = client.buffer[0];
        int size = sizeChar - '0';
        vector<string> names;
        for(int i = 1; i < a; i++) {
            bool flag = true;
            if(client.buffer[i] == '|') {
                names.push_back(tmp);
                for(int j = 0; j < playerList.size(); j++) {
                    if(tmp == playerList[j].getString().toAnsiString()) {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    Text text;
                    playerList.push_back(text3);
                    playerList[playerCounter].setFont(font);
                    playerList[playerCounter].setFillColor(color);
                    playerList[playerCounter].setString(tmp);
                    playerList[playerCounter].setCharacterSize(70);
                    playerList[playerCounter].setPosition(200, 60 * (playerCounter + 2));
                    playerCounter++;
                }
                tmp = "";
                continue;
            }
            tmp.push_back(client.buffer[i]);
        }
        if(size != playerCounter-1) {
            for(int i = 1; i < playerCounter; i++) {
                bool flag = true;
                for(string name : names) {
                    if(playerList[i].getString().toAnsiString() == name) {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    Vector2f position = playerList[i].getPosition();
                    playerList[i] = playerList[playerCounter-1];
                    playerList[i].setPosition(position);
                    playerList.pop_back();
                    playerCounter--;
                    break;
                }
            }
        }
    }
    if(playerCounter == 5) {
        string msg;
        for(char ch: name) {
            if(ch == ' ') {
                msg.push_back('_');
                continue;
            }
            msg.push_back(ch);
        }
        sleep(1);
        write(client.sock, ("(" + msg).c_str(), msg.length()+1);
        return 2;
    }


    for (const auto &i: playerList) {
        window.draw(i);
    }
    Event event{};
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyReleased) {
            if (event.key.code == Keyboard::Down) {
                downKeyClicked = true;
                color = sf::Color::Green;
            }
            if (event.key.code == Keyboard::Return && downKeyClicked) {
                string roomName;
                for(char ch : name) {
                    if(ch == ' ') {
                        roomName.push_back('_');
                        continue;
                    }
                    roomName.push_back(ch);
                }
                write(client.sock, ('*' + roomName).c_str(), roomName.length()+1);
                window.clear();
                return 0;
            }
        }
    }
    window.display();
    return 1;
}



WaitingRoom::~WaitingRoom() {

}

const string &WaitingRoom::getName() const {
    return name;
}

void WaitingRoom::setName(const string &name) {
    WaitingRoom::name = name;
}

vector<Player> WaitingRoom::getPlayers() {
    return players;
}

bool WaitingRoom::isGoBackFlag() const {
    return goBackFlag;
}


