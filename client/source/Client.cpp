//
// Created by jan-banan on 04.01.24.
//
#include "Client.h"

Client::Client() {

}

Client::~Client() {

}

char Client::validateNickAvailability(string input) {
    int count = sprintf(buffer, ("#" + input).c_str());
    write(sock, buffer, count+1);
    read(sock, buffer, 1);
    return buffer[0];
}

void Client::initialize() {
    // Main loop - Runs until the window is closed
    addrinfo *resolved, hints={.ai_flags=0, .ai_family=AF_INET, .ai_socktype=SOCK_STREAM};
    int res = getaddrinfo("localhost", "8080", &hints, &resolved);
    if(res || !resolved) error(1, 0, "getaddrinfo: %s", gai_strerror(res));

    // create socket
    sock = socket(resolved->ai_family, resolved->ai_socktype, 0);
    if(sock == -1) error(1, errno, "socket failed");

    // attept to connect
    res = connect(sock, resolved->ai_addr, resolved->ai_addrlen);
    if(res) error(1, errno, "connect failed");

    // free memory
    freeaddrinfo(resolved);
}

