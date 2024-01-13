//
// Created by jan-banan on 05.01.24.
//

#ifndef SCRABBLE_BR_CLIENT_H
#define SCRABBLE_BR_CLIENT_H

#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h>
#include <sys/epoll.h>
#include <csignal>
#include <cstdlib>
#include <vector>
#include "Player.h"
#include "WaitingRoom.h"
#include "Game.h"

class Client {
public:
    int sockfd;
    Client();
    ~Client();
    char generateRandomLetter();
};
#endif //SCRABBLE_BR_CLIENT_H
