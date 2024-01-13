#ifndef SCRABBLE_BR_GAME_H
#define SCRABBLE_BR_GAME_H
#include "Player.h"
#include "WaitingRoom.h"

class Game {
private:;
    int shrinkage;
    vector<Vector2f> dangerZones;
    vector<Player> players;
public:
    Game();
    ~Game();
    bool flag;
    array<Vector2f, 4> startingPositions;
    array<array<char, 15>, 15> gameState;
    void shrinkGrid();
    int getShrinkage();
    int playersLeft;
    bool finished;
    WaitingRoom room;
    vector<Vector2f> getDangerZones();
};


#endif //SCRABBLE_BR_GAME_H
