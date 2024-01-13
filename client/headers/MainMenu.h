#ifndef SCRABBLE_BR_MAINMENU_H
#define SCRABBLE_BR_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#define MAX_MAIN_MENU_ITEMS 4

using namespace std;
using namespace sf;


class MainMenu {
private:
    RenderWindow& window;
    RenderWindow play;
    RenderWindow options;
    RenderWindow about;
    int mainMenuSelected;
    Font font;
    Text mainMenu[MAX_MAIN_MENU_ITEMS];
    sf::Text playerText;
    bool playFlag;
    bool optionsFlag ;
    bool aboutFlag;


public:
    explicit MainMenu(RenderWindow& window);
    ~MainMenu();
    void draw();
    void moveUp();
    void moveDown();

    void setPlayFlag(bool flag);
    bool getPlayFlag() const;
    void setOptionsFlag(bool flag);
    bool getOptionsFlag() const;
    void setAboutFlag(bool flag);
    bool getAboutFlag() const;
    sf::Text getPlayerText();
    void setPlayerText(sf::String text);
    Font getFont(){
        return font;
    }
    void setNickname();
    int mainMenuPressed() const{
        return mainMenuSelected;
    }




};


#endif //SCRABBLE_BR_MAINMENU_H
