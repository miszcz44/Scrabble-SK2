#ifndef SCRABBLE_BR_PLAYER_H
#define SCRABBLE_BR_PLAYER_H

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;
using namespace sf;

class Player {
private:


public:
    string nickname;
    Player();
    ~Player();
    string getNickname();
    int sock;
    bool flag;
};


#endif //SCRABBLE_BR_PLAYER_H
