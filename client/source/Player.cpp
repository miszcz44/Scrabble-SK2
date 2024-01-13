#include <fstream>
#include "Player.h"

Player::Player(Grid& grid, MousePos& mousePos) : grid(grid), mousePos(mousePos){
    // generate random seed
    srand(time(NULL));

    // starting positions of players
    startingPositions = {Vector2f(0, 0),
                         Vector2f(0, 14),
                         Vector2f(14, 0),
                         Vector2f(14, 14)};
    // generating starting letters
    generateRandomLetters();
    // initializing blank game state
    for (auto &row : gameState) {
        for (char &cell : row) {
            cell = '0';
        }
    }

    // copy letters to be used in playerInput
    letters_copy = letters;
    gridEndFlag = false;
    wordLength = 0;
    inProgressFlag = false;
    isAlive = true;
    possiblePlace = 4;
}

Player::~Player() {

}

Vector2u Player::getPosition() const {
    return position;
}

void Player::setPosition(const Vector2u &pos) {
    position = pos;
}

char Player::getLetter() const {
    return cornerLetter;
}

void Player::setLetter(char letter, Vector2u letterPosition) {
    cornerLetter = letter;
}

char Player::generateRandomLetter() {
    return 'A' + std::rand() % 26;
}

char Player::generateRandomVowel() {
    std::string vowels = "AEIOU";
    return vowels[std::rand() % vowels.size()];
}

void Player::generateRandomLetters() {
    for (int i = 0; i < 4; i++) {
        // letters[i] = generateRandomVowel();
        letters.push_back(generateRandomVowel());
    }
    for (int i = 4; i < 8; i++) {
        // letters[i] = generateRandomConsonant();
        letters.push_back(generateRandomConsonant());
    }
}

char Player::generateRandomConsonant() {
    std::string consonants = "BCDFGHJKLMNPQRSTVWXYZ";
    return consonants[std::rand() % consonants.size()];
}

void Player::gameStateToGrid(RenderWindow &window) {
    Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    font.loadFromFile("../assets/Fonts/Arialn.ttf");
    text.setFont(font);
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (gameState[i][j] != '0') { // If the cell is not empty
                text.setString(gameState[i][j]);
                text.setCharacterSize(24); // Adjust the size as needed
                text.setPosition(i * grid.getGridSizeF() + 40, j * grid.getGridSizeF() + 35); // Adjust the position as needed
                window.draw(text);
            }
        }
    }
}
// TODO: FIX - sth wrong with font
void Player::drawLetters(RenderWindow &window) {
    Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    font.loadFromFile("../assets/Fonts/Arialn.ttf");
    text.setFont(font);
    for (int i = 0; i < 8; i++) {
        text.setString(letters[i]);
        text.setPosition(i * 100 + 25, 800);
        window.draw(text);
    }
}
// TODO: adjust for cases using already placed letters in the grid (SHTOOK)
void Player::playerInput(RenderWindow &window) {
    Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    font.loadFromFile("../assets/Fonts/Arialn.ttf");
    text.setFont(font);

    Event event;
    Vector2f pos = mousePos.getLockedTilePos();
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if(mousePos.getLockedTilePos().x != -1 && isAlive){
            if(event.type == Event::KeyPressed){
                Keyboard::Key keyCode = event.key.code;
                if(keyCode >= Keyboard::A && keyCode <= Keyboard::Z){
                    char letter = 'A' + keyCode - Keyboard::A;

                    auto it = std::find(letters_copy.begin(), letters_copy.end(), letter);
                    if (it != letters_copy.end()) {
                        text.setString(letter);
                        Vector2f newPos;
                        Event event1;
                        switch(mousePos.getArrowDirection()){
                            case MousePos::UP:
                                if(gridEndFlag || pos.y == 0 ||
                                (pos.y < 14 && gameState[pos.x][pos.y+1] != '0') ||
                                (gameState[pos.x][pos.y-1] != '0' && !inProgressFlag)) {
                                    break;
                                }
                                mousePos.directionFlag = false;
                                if(pos.y > 0){
                                    bool localFlag = true;
                                    for(int i = pos.y - wordLength - 1; i >= 0; i--) {
                                        inProgressFlag = true;
                                        if(i == 0) {
                                            gridEndFlag = true;
                                        }
                                        if(gameState[pos.x][i] == '0') {
                                            newPos = (Vector2f(pos.x,i));
                                            word.push_back(letter);
                                            if(i >= 1 && gameState[pos.x][i-1] != '0') {
                                                if(i>= 2 && gameState[pos.x][i-1] != '0'
                                                   && gameState[pos.x][i-2] != '0'){
                                                    word.push_back('6');
                                                    localFlag = false;
                                                }
                                                else{
                                                    word.push_back(gameState[pos.x][i-1]);
                                                }
                                            }
                                            break;
                                        }
//
                                    }
                                    if(!localFlag ||
                                       find(startingPositions.begin(), startingPositions.end(), newPos) !=
                                       startingPositions.end()) break;
                                    gameState[newPos.x][newPos.y] = letter;
                                    savedPositions.push_back(newPos);
                                    string str(word.begin(), word.end());
                                    text.setPosition(newPos.x * grid.getGridSizeF() + 40, newPos.y * grid.getGridSizeF() + 35);
                                    window.draw(text);
                                    letters_copy.erase(it);
                                    wordLength++;
                                }
                                break;
                            case MousePos::DOWN:
                                if(gridEndFlag || pos.y == 14 ||
                                (pos.y > 0 && gameState[pos.x][pos.y-1] != '0') ||
                                (gameState[pos.x][pos.y+1] != '0' && !inProgressFlag)) {
                                    break;
                                }
                                mousePos.directionFlag = false;
                                if(pos.y < 14){
                                    bool localFlag = true;
                                    for(int i = pos.y + wordLength + 1; i < 15; i++) {
                                        inProgressFlag = true;
                                        if(i == 0) {
                                            gridEndFlag = true;
                                        }
                                        if(gameState[pos.x][i] == '0') {
                                            newPos = (Vector2f(pos.x,i));
                                            word.push_back(letter);
                                            if(i <= 13 && gameState[pos.x][i+1] != '0') {
                                                if(i <= 12 && gameState[pos.x][i+1] != '0'
                                                   && gameState[pos.x][i+2] != '0') {
                                                    word.push_back('6');
                                                    localFlag = false;
                                                }
                                                else {
                                                    word.push_back(gameState[pos.x][i+1]);
                                                }
                                            }
                                            break;
                                        }
                                    }
                                    if(!localFlag ||
                                       find(startingPositions.begin(), startingPositions.end(), newPos) !=
                                       startingPositions.end()) break;
                                    gameState[newPos.x][newPos.y] = letter;
                                    savedPositions.push_back(newPos);
                                    string str(word.begin(), word.end());
                                    text.setPosition(newPos.x * grid.getGridSizeF() + 40, newPos.y * grid.getGridSizeF() + 35);
                                    window.draw(text);
                                    letters_copy.erase(it);
                                    wordLength++;
                                }
                                break;
                            case MousePos::LEFT:
                                if(gridEndFlag || pos.x == 0 ||
                                (pos.x < 14 && gameState[pos.x+1][pos.y] != '0') ||
                                (gameState[pos.x-1][pos.y] != '0' && !inProgressFlag)) {
                                    break;
                                }
                                mousePos.directionFlag = false;
                                if(pos.x > 0){
                                    bool localFlag = true;
                                    for(int i = pos.x - wordLength - 1; i >= 0; i--) {
                                        inProgressFlag = true;
                                        if(i == 0) {
                                            gridEndFlag = true;
                                        }
                                        if(gameState[i][pos.y] == '0') {
                                            newPos = (Vector2f(i,pos.y));
                                            word.push_back(letter);
                                            if(i >= 1 && gameState[i-1][pos.y] != '0') {
                                                if(i >= 2 && gameState[i-1][pos.y] != '0'
                                                   && gameState[i-2][pos.y] != '0'){
                                                    word.push_back('6');
                                                    localFlag = false;
                                                }
                                                else {
                                                    word.push_back(gameState[i-1][pos.y]);
                                                }
                                            }
                                            break;
                                        }
                                    }
                                    if(!localFlag ||
                                    find(startingPositions.begin(), startingPositions.end(), newPos) !=
                                    startingPositions.end()) break;
                                    gameState[newPos.x][newPos.y] = letter;
                                    savedPositions.push_back(newPos);
                                    string str(word.begin(), word.end());
                                    text.setPosition(newPos.x * grid.getGridSizeF() + 40, newPos.y * grid.getGridSizeF() + 35);
                                    window.draw(text);
                                    letters_copy.erase(it);
                                    wordLength++;
                                }
                                break;
                            case MousePos::RIGHT:
                                if(gridEndFlag || pos.x == 14 ||
                               (pos.x > 0 && gameState[pos.x-1][pos.y] != '0') ||
                                (gameState[pos.x+1][pos.y] != '0' && !inProgressFlag)) {
                                    break;
                                }
                                mousePos.directionFlag = false;
                                if(pos.x < 14){
                                    bool localFlag = true;
                                    for(int i = pos.x + wordLength + 1; i < 15; i++) {
                                        inProgressFlag = true;
                                        if(i == 14) {
                                            gridEndFlag = true;
                                        }
                                        if(gameState[i][pos.y] == '0') {
                                            newPos = (Vector2f(i,pos.y));
                                            word.push_back(letter);
                                            if(i <= 13 && gameState[i+1][pos.y] != '0') {
                                                if(i <= 12 && gameState[i+1][pos.y] != '0'
                                                   && gameState[i+2][pos.y] != '0'){
                                                    word.push_back('6');
                                                    localFlag = false;
                                                }
                                                else {
                                                    word.push_back(gameState[i+1][pos.y]);
                                                }
                                            }
                                            break;
                                        }

                                    } // y
                                    if(!localFlag ||
                                       find(startingPositions.begin(), startingPositions.end(), newPos) !=
                                       startingPositions.end()) break;
                                    gameState[newPos.x][newPos.y] = letter;
                                    savedPositions.push_back(newPos);
                                    string str(word.begin(), word.end());
                                    text.setPosition(newPos.x * grid.getGridSizeF() + 40, newPos.y * grid.getGridSizeF() + 35);
                                    window.draw(text);
                                    letters_copy.erase(it);
                                    wordLength++;
                                }
                                break;
                            case MousePos::NONE:
                                break;
                        }
                        string str(word.begin(), word.end());
                    }
                }
                if (event.key.code == Keyboard::Return) {
                    vector<char> dummyWord = word;
                    dummyWord.insert(dummyWord.begin(), gameState[pos.x][pos.y]);
                    string str(dummyWord.begin(), dummyWord.end());
                    if(!validateWord(str)) {
                        for (Vector2f savedPosition: savedPositions) {
                            gameState[savedPosition.x][savedPosition.y] = '0';
                        }
                    }
                    else {
                        words.push_back(str);
                        for (Vector2f savedPosition: savedPositions) {
                            playerPositions.push_back(savedPosition);
                        }
                        string msg;
                        msg.push_back(')');
                        for(int i = 0; i < 15; i++) {
                            for(int j = 0; j < 15; j++) {
                                msg.push_back(gameState[i][j]);
                            }
                        }
                        write(sock, msg.c_str(), msg.size()+1);
                        letters.clear();
                        generateRandomLetters();
                        switch(mousePos.getArrowDirection()){
                            case MousePos::UP:
                                currentWordCoordinates = Vector2f(pos.x, pos.y - (float) wordLength);
                                break;
                            case MousePos::DOWN:
                                currentWordCoordinates = Vector2f(pos.x, pos.y + (float) wordLength);
                                break;
                            case MousePos::LEFT:
                                currentWordCoordinates = Vector2f(pos.x - (float) wordLength, pos.y);
                                break;
                            case MousePos::RIGHT:
                                currentWordCoordinates = Vector2f(pos.x + (float) wordLength, pos.y );
                                break;
                        }
                    }
                    letters_copy = letters;
                    savedPositions.clear();
                    word.clear();
                    mousePos.arrowDirection = MousePos::NONE;
                    mousePos.directionFlag = true;
                    gridEndFlag = false;
                    wordLength = 0;
                    inProgressFlag = false;
                }
            }
        }
    }
}

bool Player::validateWord(string word) {
    ifstream file("../assets/dictionary.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }
    string line;
    while (std::getline(file, line)) {
        if (line == word) {
            return true;
        }
    }
    return false;
}

array<array<char, 15>, 15> Player::getGameState() {
    return gameState;
}

void Player::setGameState(array<array<char, 15>, 15> state) {
    gameState = state;
}

Vector2f Player::getCurrentCoordinates() {
    return currentWordCoordinates;
}

void Player::setAliveFlag(bool flag) {
    isAlive = flag;
}

void Player::playerDead(RenderWindow &window){
    sf::Sprite deadSprite;
    if (texture.loadFromFile("../assets/skull.png", sf::IntRect(0, 0, 100, 100)))
    {
        deadSprite.setTexture(texture);
        if(startingPosition == 0) {
            deadSprite.setPosition(0, 0);
        }
        else if(startingPosition == 1) {
            deadSprite.setPosition(0, 700);
        }
        else if(startingPosition == 2) {
            deadSprite.setPosition(700, 0);
        }
        else if(startingPosition == 3) {
            deadSprite.setPosition(700, 700);
        }

    }
    char intChar[2];
    sprintf(intChar, "%d", possiblePlace);
    for(Vector2f startPosition : startingPositions) {
        gameState[startPosition.x][startPosition.y] = intChar[0];
    }
    window.draw(deadSprite);
}

bool Player::getAliveFlag() {
    return isAlive;
}

void Player::setNickname(string nick) {
    nickname = nick;
}

string Player::getNickname() {
    return nickname;
}

void Player::clear() {
    letters_copy = letters;
    gridEndFlag = false;
    wordLength = 0;
    inProgressFlag = false;
    isAlive = true;
    possiblePlace = 4;
    playerPositions.clear();
    words.clear();
}
