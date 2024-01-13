//
// Created by mck on 1/2/24.
//

#ifndef SCRABBLE_BR_SERVER_H
#define SCRABBLE_BR_SERVER_H
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstdio>
#include <error.h>

#include "MainMenu.h"
#include "Player.h"
#include "WaitingRoom.h"
#include "Game.h"
#include "Lobby.h"

class Server {
private:
    int port;
    int fd;
    int client_fd;
    int addrlen = sizeof(address);
    struct sockaddr_in address;
    char buffer[1024];
    int roomCounter;
public:
    Server();
    ~Server();
    int startServer();
    void startListen();
    void acceptConnection();
    void closeConnection();
};


#endif //SCRABBLE_BR_SERVER_H
