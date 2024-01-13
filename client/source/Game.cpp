#include "Game.h"

Game::Game(Player& player) : player(player)
{
    gameState = player.getGameState();
    srand(time(NULL));
    shrinkage = 0;

}

Game::~Game() {

}

void Game::checkIfPlayerKilled() {
    for(Vector2f zone : dangerZones) {
        if(player.getCurrentCoordinates() == zone) {
            player.setAliveFlag(false);
            break;
        }
    }
    for(Vector2f coords : player.playerPositions) {
        string potentialWord;
        Vector2f wordStartCoords;
        Vector2f wordEndCoords;
        if(coords.x != 0 && coords.x != 14 && coords.y != 0 && coords.y != 14) {
            if(player.gameState[coords.x-1][coords.y] != '0' && find(player.playerPositions.begin(),
        player.playerPositions.end(), Vector2f(coords.x-1, coords.y)) == player.playerPositions.end() &&
            find(player.savedPositions.begin(),player.savedPositions.end(),
             Vector2f(coords.x-1, coords.y)) == player.savedPositions.end()) {
                wordStartCoords = Vector2f(coords.x-1, coords.y);
                int incr = 1;
                while(coords.x-1-incr >= 0) {
                    if(player.gameState[coords.x-1-incr][coords.y] == '0' || find(player.playerPositions.begin(),
                    player.playerPositions.end(), Vector2f(coords.x-1-incr, coords.y)) != player.playerPositions.end() ||
                     find(player.savedPositions.begin(),player.savedPositions.end(),
                          Vector2f(coords.x-1-incr, coords.y)) != player.savedPositions.end()) {
                        break;
                    }
                    wordStartCoords = Vector2f(coords.x-1-incr, coords.y);
                    incr++;
                }
                wordEndCoords = Vector2f(coords.x, coords.y);
                incr = 1;
                while(coords.x+incr <= 14) {
                    if(player.gameState[coords.x+incr][coords.y] == '0' || find(player.playerPositions.begin(),
                player.playerPositions.end(), Vector2f(coords.x+incr, coords.y)) != player.playerPositions.end() ||
                   find(player.savedPositions.begin(),player.savedPositions.end(),
                        Vector2f(coords.x+incr, coords.y)) != player.savedPositions.end()) {
                        break;
                    }
                    wordEndCoords = Vector2f(coords.x+incr, coords.y);
                    incr++;
                }
                for(int i = wordStartCoords.x; i <= wordEndCoords.x; i++) {
                    potentialWord.push_back(player.gameState[i][coords.y]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                  player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
                for(int i = wordEndCoords.x; i >= wordStartCoords.x; i--) {
                    potentialWord.push_back(player.gameState[i][coords.y]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                  player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
            }
            else if(player.gameState[coords.x+1][coords.y] != '0' && find(player.playerPositions.begin(),
                player.playerPositions.end(), Vector2f(coords.x+1, coords.y)) == player.playerPositions.end() &&
                    find(player.savedPositions.begin(),player.savedPositions.end(),
                         Vector2f(coords.x+1, coords.y)) == player.savedPositions.end()) {
                wordStartCoords = Vector2f(coords.x, coords.y);
                wordEndCoords = Vector2f(coords.x+1, coords.y);
                int incr = 1;
                while(coords.x+1+incr <= 14) {
                    if(player.gameState[coords.x+1+incr][coords.y] == '0' || find(player.playerPositions.begin(),
             player.playerPositions.end(), Vector2f(coords.x+1+incr, coords.y)) != player.playerPositions.end() ||
                    find(player.savedPositions.begin(),player.savedPositions.end(),
                         Vector2f(coords.x+1+incr, coords.y)) != player.savedPositions.end()) {
                        break;
                    }
                    wordEndCoords = Vector2f(coords.x+1+incr, coords.y);
                    incr++;
                }
                for(int i = wordStartCoords.x; i <= wordEndCoords.x; i++) {
                    potentialWord.push_back(player.gameState[i][coords.y]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                  player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
                for(int i = wordEndCoords.x; i >= wordStartCoords.x; i--) {
                    potentialWord.push_back(player.gameState[i][coords.y]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                  player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
            }
            if(player.gameState[coords.x][coords.y-1] != '0' && find(player.playerPositions.begin(),
          player.playerPositions.end(), Vector2f(coords.x, coords.y-1)) == player.playerPositions.end() &&
                find(player.savedPositions.begin(),player.savedPositions.end(),
                     Vector2f(coords.x, coords.y-1)) == player.savedPositions.end()) {
                wordStartCoords = Vector2f(coords.x, coords.y-1);
                int incr = 1;
                while(coords.y-1-incr >= 0) {
                    if(player.gameState[coords.x][coords.y-1-incr] == '0' || find(player.playerPositions.begin(),
           player.playerPositions.end(), Vector2f(coords.x, coords.y-1-incr)) != player.playerPositions.end() ||
                    find(player.savedPositions.begin(),player.savedPositions.end(),
                         Vector2f(coords.x, coords.y-1-incr)) != player.savedPositions.end()) {
                        break;
                    }
                    wordStartCoords = Vector2f(coords.x, coords.y-1-incr);
                    incr++;
                }
                wordEndCoords = Vector2f(coords.x, coords.y);
                incr = 1;
                while(coords.y+incr <= 14) {
                    if(player.gameState[coords.x][coords.y+incr] == '0' || find(player.playerPositions.begin(),
             player.playerPositions.end(), Vector2f(coords.x, coords.y+incr)) != player.playerPositions.end() ||
                    find(player.savedPositions.begin(),player.savedPositions.end(),
                         Vector2f(coords.x, coords.y+incr)) != player.savedPositions.end()) {
                        break;
                    }
                    wordEndCoords = Vector2f(coords.x, coords.y+incr);
                    incr++;
                }
                for(int i = wordStartCoords.y; i <= wordEndCoords.y; i++) {
                    potentialWord.push_back(player.gameState[coords.x][i]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                  player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
                for(int i = wordEndCoords.y; i >= wordStartCoords.y; i--) {
                    potentialWord.push_back(player.gameState[coords.x][i]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                      player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
            }
            else if(player.gameState[coords.x][coords.y+1] != '0' && find(player.playerPositions.begin(),
           player.playerPositions.end(), Vector2f(coords.x, coords.y+1)) == player.playerPositions.end() &&
                    find(player.savedPositions.begin(),player.savedPositions.end(),
                         Vector2f(coords.x, coords.y+1)) == player.savedPositions.end()) {
                wordStartCoords = Vector2f(coords.x, coords.y);
                wordEndCoords = Vector2f(coords.x, coords.y+1);
                int incr = 1;
                while(coords.y+1+incr <= 14) {
                    if(player.gameState[coords.x][coords.y+1+incr] == '0' || find(player.playerPositions.begin(),
           player.playerPositions.end(), Vector2f(coords.x, coords.y+1+incr)) != player.playerPositions.end() ||
                    find(player.savedPositions.begin(),player.savedPositions.end(),
                     Vector2f(coords.x, coords.y+1+incr)) != player.savedPositions.end()) {
                        break;
                    }
                    wordEndCoords = Vector2f(coords.x, coords.y+1+incr);
                    incr++;
                }
                for(int i = wordStartCoords.y; i <= wordEndCoords.y; i++) {
                    potentialWord.push_back(player.gameState[coords.x][i]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                  player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
                for(int i = wordEndCoords.y; i >= wordStartCoords.y; i--) {
                    potentialWord.push_back(player.gameState[coords.x][i]);
                }
                if(player.validateWord(potentialWord) && find(player.words.begin(),
                  player.words.end(), potentialWord) == player.words.end() && potentialWord.length() > 2) {
                    cout << "kaszanka" << endl;
                    cout << potentialWord << endl;
                    cout << "kaszanka" << endl;
                    player.setAliveFlag(false);
                    break;
                }
                else {
                    potentialWord = "";
                }
            }
        }
    }
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

void Game::clear() {
    shrinkage = 0;
    dangerZones.clear();
}
