#include "MainMenu.h"

MainMenu:: MainMenu(sf::RenderWindow& window) : window(window) {
        // Load font
        if (!font.loadFromFile("../assets/Fonts/Arialn.ttf")) {
            cout << "Error loading font" << endl;
        }
        // Initialize main menu
        // Play button
        mainMenu[0].setFont(font);
        mainMenu[0].setFillColor(sf::Color::Red);
        mainMenu[0].setString("Type ur name");
        mainMenu[0].setCharacterSize(70);
        mainMenu[0].setPosition(300, 200);
        // Options button
        mainMenu[1].setFont(font);
        mainMenu[1].setFillColor(sf::Color::Red);
        mainMenu[1].setString(playerText.getString());
        mainMenu[1].setCharacterSize(70);
        mainMenu[1].setPosition(300, 300);
        // About button
        mainMenu[2].setFont(font);
        mainMenu[2].setFillColor(sf::Color::Red);
        mainMenu[2].setString("Play");
        mainMenu[2].setCharacterSize(70);
        mainMenu[2].setPosition(400, 400);
        // Exit button
        mainMenu[3].setFont(font);
        mainMenu[3].setFillColor(sf::Color::Red);
        mainMenu[3].setString("Exit");
        mainMenu[3].setCharacterSize(70);
        mainMenu[3].setPosition(400, 500);

        mainMenuSelected = 1;

        // Input flags
        playFlag = false;
        optionsFlag = false;
        aboutFlag = false;

}

MainMenu::~MainMenu() = default;

void MainMenu::setNickname(){
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::Red);
    mainMenu[1].setString(playerText.getString());
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(300, 300);
}

void MainMenu::setPlayFlag(bool flag){
    playFlag = flag;
}
bool MainMenu::getPlayFlag() const{
    return playFlag;
}
void MainMenu::setOptionsFlag(bool flag){
    optionsFlag = flag;
}
bool MainMenu::getOptionsFlag() const{
    return optionsFlag;
}
void MainMenu::setAboutFlag(bool flag){
    aboutFlag = flag;
}
bool MainMenu::getAboutFlag() const{
    return aboutFlag;
}

void MainMenu::draw() {
    for (const auto & i : mainMenu) {
        window.draw(i);
    }
}

void MainMenu::moveUp() {
    if (mainMenuSelected - 1 >= 2) {
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Red);
        mainMenuSelected--;
        if (mainMenuSelected == -1) {
            mainMenuSelected = 3;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Green);
    }
}

void MainMenu::moveDown() {
    if (mainMenuSelected  <= MAX_MAIN_MENU_ITEMS) {
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Red);
        mainMenuSelected++;
        if (mainMenuSelected == 4) {
            mainMenuSelected = 2;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Green);
    }
}

sf::Text MainMenu::getPlayerText() {
    return playerText;
}

void MainMenu::setPlayerText(sf::String text) {
    playerText.setString(text);
}





