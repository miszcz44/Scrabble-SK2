//
// Created by mck on 1/2/24.
//

#include "Server.h"

Server::Server() {
    port = 8080;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if(startServer() != 0){
        perror("Failed to start server");
        exit(EXIT_FAILURE);
    }
    startListen();

}

Server::~Server() {

}

void Server::startListen() {
    if (listen(fd, 1) < 0) {
        perror("socket listen failed");
        exit(EXIT_FAILURE);
    }

    while(true){
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        auto clientFd = accept(fd, (sockaddr*)&client_addr, &client_addr_len);
        if(clientFd < 0){
            perror("socket accept failed");
            exit(EXIT_FAILURE);
        }

    }
}

void Server::closeConnection() {
    close(fd);
    close(client_fd);
    exit(0);
}

void Server::acceptConnection() {
    if ((client_fd = accept(fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

int Server::startServer() {
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        return 1;
    }

    if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }
    return 0;
}
