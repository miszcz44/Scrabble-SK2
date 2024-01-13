//
// Created by jan-banan on 05.01.24.
//
#include <Client.h>

Client::Client() {
}

Client::~Client() {

}

char Client::generateRandomLetter() {
    std::string letters = "WZKAM";
    return letters[std::rand() % letters.size()];
}