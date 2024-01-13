//
// Created by jan-banan on 04.01.24.
//

#ifndef SCRABBLE_BR_CLIENT_H
#define SCRABBLE_BR_CLIENT_H
#include <bits/stdc++.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <thread>

using namespace std;

class Client {
public:
    Client();
    ~Client();
    int sock;
    char validateNickAvailability(string input);
    char buffer[256];
    void initialize();

private:

    static Client* client;
};
#endif //SCRABBLE_BR_CLIENT_H
