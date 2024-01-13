////
//// Created by erykb on 30.12.2023.
////
#ifndef SCRABBLE_BR_WAITINGROOM_H
#define SCRABBLE_BR_WAITINGROOM_H

#include <string>
#include "Player.h"

using namespace std;

class WaitingRoom {
private:

public:
    WaitingRoom();
    ~WaitingRoom();
    string name;
    vector<Player> players;
};
//
#endif //SCRABBLE_BR_WAITINGROOM_H
