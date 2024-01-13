#ifndef SCRABBLE_BR_PLAYER_H
#define SCRABBLE_BR_PLAYER_H

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include "Grid.h"
#include "MousePos.h"
#include "Client.h"

using namespace std;
using namespace sf;

class Player {
private:



public:
    Vector2u position;
    char cornerLetter;      // At first the letter in the corner,  then the selected letter
    vector<char> letters;
    vector<char> letters_copy;
    array<Vector2f, 4> startingPositions;
    int startingPosition;
    Vector2f currentWordCoordinates;
    array<array<char, 15>, 15> gameState;
    vector<char> word;
    vector<Vector2f> savedPositions;
    vector<Vector2f> playerPositions;
    vector<string> words;
    int wordLength;
    int directionFlag;
    bool inProgressFlag;
    Grid &grid;
    MousePos &mousePos;
    Font font;
    bool gridEndFlag;
    bool isAlive;
    sf::Texture texture;
    string nickname;
    Player(Grid& grid, MousePos& mousePos);
    ~Player();
    int sock;
    Vector2u getPosition() const;
    void setPosition(const Vector2u& pos);
    int possiblePlace;

    char getLetter() const;
    void setLetter(char letter, Vector2u letterPosition);

    static char generateRandomLetter();
    static char generateRandomVowel();
    static char generateRandomConsonant();

    void gameStateToGrid(RenderWindow &window);
    void drawLetters(RenderWindow &window);

    void playerInput(RenderWindow &window);
    array<array<char, 15>, 15> getGameState();

    bool validateWord(string word);
    void clear();
    void generateRandomLetters();
    void setGameState(array<array<char, 15>, 15> state);
    Vector2f getCurrentCoordinates();
    void setAliveFlag(bool flag);
    bool getAliveFlag();

    void playerDead(RenderWindow &window);
    void setNickname(string nick);
    string getNickname();
};


#endif //SCRABBLE_BR_PLAYER_H
