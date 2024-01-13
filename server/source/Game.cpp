#include "Game.h"

Game::Game()
{
    startingPositions = {Vector2f(0, 0),
                         Vector2f(0, 14),
                         Vector2f(14, 0),
                         Vector2f(14, 14)};
    srand(time(NULL));
    shrinkage = 0;
    flag = false;
    playersLeft = 4;
    finished = false;
}

Game::~Game() {

}

void Game::shrinkGrid() {
    dangerZones.clear();
    for(int i = 0; i < 1 + shrinkage; i++){
        for(int j = 0; j < 15; j++){
            dangerZones.push_back(Vector2f(i,j));
            dangerZones.push_back(Vector2f(14-i,j));
            dangerZones.push_back(Vector2f(j,i));
            dangerZones.push_back(Vector2f(j,14-i));

        }
    }
    shrinkage++;
}

int Game::getShrinkage() {
    return shrinkage;
}

vector<Vector2f> Game::getDangerZones() {
    return dangerZones;
}
