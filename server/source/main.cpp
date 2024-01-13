#include <cstdio>
#include <Game.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <csignal>
#include <Player.h>
#include <error.h>
#include <cstdlib>
#include <Client.h>
#include <unordered_map>
#include <unistd.h>
#include <WaitingRoom.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>

vector<Player> players;
vector<WaitingRoom> rooms;
vector<Game> games;
int servFd {};
std::unordered_map<int, Client> clients;
Player player;
int roomCounter = 1;

void removePlayerFromRooms(int sock) {
    for(int j = 0; j < rooms.size(); j++) {
        for(int k = 0; k < rooms[j].players.size(); k++) {
            if(rooms[j].players[k].sock == sock) {
                rooms[j].players[k] = rooms[j].players[rooms[j].players.size()-1];
                rooms[j].players.pop_back();
                break;
            }
        }
    }
}
bool handleEvent(Client &client) {
    char buffer[256];
    int n = read(client.sockfd, buffer, 255);
    if (n > 0) {
        if(buffer[0] == '#') {
            string tmp;
            for(int i = 1; i < n-1; i++) {
                tmp.push_back(buffer[i]);
            }
            char answer = '1';
            for(Player player : players) {
                if(player.getNickname() == tmp) {
                    answer = '0';
                    break;
                }
            }
            send(client.sockfd, &answer, 1, MSG_DONTWAIT);
            if(answer == '1') {
                player.nickname = tmp;
                player.sock = client.sockfd;
                players.push_back(player);
            }
        }
        else if(buffer[0] == '@') {
            WaitingRoom room;
            room.name = "Waiting room" + to_string(roomCounter);
            for(Player player: players) {
                if(player.sock == client.sockfd) {
                    room.players.push_back(player);
                    break;
                }
            }
            rooms.push_back(room);
            ssize_t a = send(client.sockfd, room.name.c_str(), room.name.length()+1, MSG_DONTWAIT);
            roomCounter++;
        }
        else if(buffer[0] == '%') {
            string tmp;
            for(WaitingRoom room : rooms) {
                tmp.append(room.name + "|" + to_string(room.players.size()) + "/4");
                tmp.append(".");
            }
            send(client.sockfd, tmp.c_str(), tmp.length()+1, MSG_DONTWAIT);
        }
        else if(buffer[0] == '^'){
            string tmp;
            for(int i = 1; i < n; i++) {
                if(buffer[i] == '_') {
                    tmp.push_back(' ');
                    continue;
                }
                tmp.push_back(buffer[i]);
            }
            for(int i = 0; i < rooms.size(); i++) {
                string roomClientName = rooms[i].name;
                if(roomClientName == tmp) {
                    for(Player player: players) {
                        if(player.sock == client.sockfd) {
                            rooms[i].players.push_back(player);
                            break;
                        }
                    }
                }
            }
        }
        else if (buffer[0] == '$'){
            string tmp;
            for(int i = 1; i < n; i++) {
                if(buffer[i] == '_') {
                    tmp.push_back(' ');
                    continue;
                }
                tmp.push_back(buffer[i]);
            }
            string msg;
            for(WaitingRoom room : rooms) {
                if(room.name == tmp) {
                    msg.append(to_string(room.players.size()));
                    for(Player player1 : room.players) {
                        msg.append(player1.nickname);
                        msg.append("|");
                    }
                    break;
                }
            }
            send(client.sockfd, msg.c_str(), msg.length() + 1, MSG_DONTWAIT);
        }
        else if(buffer[0] == '*') {
            string tmp;
            for(int i = 1; i < n; i++) {
                if(buffer[i] == '_') {
                    tmp.push_back(' ');
                    continue;
                }
                tmp.push_back(buffer[i]);
            }
            for(int i = 0; i < rooms.size(); i++) {
                if(rooms[i].name == tmp) {
                    int cnt = 0;
                    for(Player player: rooms[i].players) {
                        if(player.sock == client.sockfd) {
                            Player tmpPlayer = rooms[i].players[rooms[i].players.size()-1];
                            rooms[i].players[rooms[i].players.size()-1] = player;
                            rooms[i].players[cnt] = tmpPlayer;
                            rooms[i].players.pop_back();
                            if(rooms[i].players.size() == 0) {
                                rooms[i] = rooms[rooms.size()-1];
                                rooms.pop_back();
                            }
                            break;
                        }
                        cnt++;
                    }
                    break;
                }
            }
        }
        else if(buffer[0] == '(') {
            string tmp;
            for(int i = 1; i < n; i++) {
                if(buffer[i] == '_') {
                    tmp.push_back(' ');
                    continue;
                }
                tmp.push_back(buffer[i]);
            }
            bool flag2 = false;
            for(int i = 0; i < games.size(); i++) {
                for(Player player: games[i].room.players) {
                    if(player.sock == client.sockfd) {
                        if(games[i].finished) {
                            games[i] = games[games.size() - 1];
                            games.pop_back();
                            flag2 = true;
                            break;
                        }
                    }
                }
                if(flag2) break;
            }
            bool flag = true;
            for(Game game : games) {
                for(Player player : game.room.players) {
                    if(player.sock == client.sockfd && game.playersLeft == 4) {
                        flag = false;
                        break;
                    }
                }
                if(!flag) break;
            }
            if(flag) {
                Game game;
                for (auto &row : game.gameState) {
                    for (char &cell : row) {
                        cell = '0';
                    }
                }
                for(WaitingRoom room : rooms) {
                    if(room.name == tmp) {
                        game.room = room;
                        break;
                    }
                }
                games.push_back(game);
            }
        }
        else if(buffer[0] == '!') {
            bool flag = false;
            for(int j = 0; j < games.size(); j++) {
                for(int i = 0; i < games[j].room.players.size(); i++) {
                    if(games[j].room.players[i].sock == client.sockfd && !games[j].finished) {
                        char letter = client.generateRandomLetter();
                        Vector2f coords = games[j].startingPositions[i];
                        games[j].gameState[coords.x][coords.y] = letter;
                        send(client.sockfd, (to_string(i) + letter).c_str(), 2, MSG_DONTWAIT);
                        flag = true;
                        for(int k = 0; k < rooms.size(); k++) {
                            if(rooms[k].name == games[j].room.name) {
                                rooms[k] = rooms[rooms.size() -1];
                                rooms.pop_back();
                            }
                        }
                        break;
                    }
                }
                if(flag) break;
            }
        }
        else if(buffer[0] == '&') {
            string msg;
            bool flag = true;
            for(int i = 0; i < games.size(); i++) {
                for(Player player : games[i].room.players) {
                    if(player.sock == client.sockfd) {
                        for(int k = 0; k < 15; k++) {
                            for(int j = 0; j < 15; j++) {
                                msg.push_back(games[i].gameState[k][j]);
                            }
                        }
                        flag = false;
                        break;
                    }
                }
                if(!flag) break;
            }

            write(client.sockfd, msg.c_str(), msg.size());
        }
        else if(buffer[0] == ')') {
            int cnt = 1;
            bool flag = false;
            for(int i = 0; i < games.size(); i++) {
                for(Player player : games[i].room.players) {
                    if(player.sock == client.sockfd) {
                        for(int k = 0; k < 15; k++) {
                            for(int j = 0; j < 15; j++) {
                                games[i].gameState[k][j] = buffer[cnt];
                                cnt++;
                            }
                        }
                        flag = true;
                        break;
                    }
                }
                if(flag) break;
            }

        }
        else if(buffer[0] == '{') {
            bool flag = false;
            for(int i = 0; i < games.size(); i++) {
                for (Player player: games[i].room.players) {
                    if (player.sock == client.sockfd) {
                        string msg = to_string(games[i].playersLeft);
                        char intChar[2];
                        sprintf(intChar, "%d", games[i].playersLeft);
                        games[i].playersLeft--;

                        send(client.sockfd, msg.c_str(), 1, MSG_DONTWAIT);
                        if(games[i].playersLeft == 0) {
                            games[i].finished = true;
                        }
                        flag = true;
                        break;
                    }
                }
                if(flag) break;
            }
        }
        return true;
    }
    return false;
}

void ctrl_c(int) {
    for(auto& client : clients) {
        clients.erase(client.second.sockfd);
    }
    close(servFd);
    exit(0);
}

int main(int argc, char** argv) {

    int port = 8080;

    signal(SIGINT, ctrl_c);

    servFd = socket(AF_INET, SOCK_STREAM, 0);
    if (servFd == -1) {
        error(1, errno, "socket failed");
    }
    int optVal = 1;
    setsockopt(servFd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof optVal);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons((short)port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int res = bind(servFd, (sockaddr*) &serverAddr, sizeof(serverAddr));
    if(res) error(1, errno, "bind failed");

    res = listen(servFd, SOMAXCONN);
    if(res) error(1, errno, "listen failed");

    int epollFd = epoll_create1(0);
    epoll_event ee{};
    ee.data.fd = servFd;
    ee.events = EPOLLIN;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, servFd, &ee); // dodanie gniazda serwera do epolla

    while (true) {
        epoll_event events[100];
        int eventsNumber = epoll_wait(epollFd, events, 100, -1); // czekaj na zdarzenia
        if(eventsNumber == -1 ) {
            error(0, errno, "epoll_wait failed");
            ctrl_c(SIGINT);
        }
        for (int i = 0; i < eventsNumber; ++i) {
            int fd = events[i].data.fd;
            if (fd == servFd) {
                sockaddr_in clientAddr{};
                socklen_t clientAddrSize = sizeof(clientAddr);
                int clientFd = accept(servFd, (sockaddr*) &clientAddr, &clientAddrSize);
                if(clientFd == -1) error(1, errno, "listen failed");
                int flags = fcntl(clientFd, F_GETFL, 0);
                fcntl(clientFd, F_SETFL, flags | O_NONBLOCK); // tryb nieblokujacy

                ee.data.fd = clientFd;
                ee.events = EPOLLIN;
                epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &ee); // dodanie gniazda klienta do epolla
                Client client;
                client.sockfd = clientFd;
                clients[clientFd] = client;
            }
            else {
                Client &client = clients[fd];
                if (events[i].events & EPOLLIN && !handleEvent(client)) {
                    removePlayerFromRooms(client.sockfd);
                    epoll_ctl(epollFd, EPOLL_CTL_DEL, client.sockfd, &events[i]);
                    clients.erase(client.sockfd);
                }
            }
        }
    }
}


