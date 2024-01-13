#ifndef SCRABBLE_BR_GAME_H
#define SCRABBLE_BR_GAME_H
#include "Player.h"

class Game {
private:
    array<array<char, 15>, 15> gameState;
    Player& player;
    int shrinkage;
    vector<Vector2f> dangerZones;
    vector<Player> players;
public:
    Game(Player& player);
    ~Game();
    bool flag;
    void clear();
    void shrinkGrid();
    int getShrinkage();
    void checkIfPlayerKilled();
    vector<Vector2f> getDangerZones();
};


#endif //SCRABBLE_BR_GAME_H
