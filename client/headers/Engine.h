#ifndef SCRABBLE_BR_ENGINE_H
#define SCRABBLE_BR_ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Grid.h>
#include <MousePos.h>
#include <MainMenu.h>
#include "Player.h"
#include "Game.h"
#include <Lobby.h>
#include <Client.h>

using namespace std;
using namespace sf;

class Engine {
private:
    // Window
    Vector2f resolution;
    RenderWindow window;
    View view;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;
    float dt = 0.f;
    Clock dtClock;

    Lobby lobby;
    Grid grid;
    MousePos mousePos;
    MainMenu mainMenu;
    View mainMenuView;
    Player player;
    Game game;
    WaitingRoom waitingRoom;
    Client client;
    Clock clock;
    string playerInput;
    bool flag;
    bool startFlag;
    bool cornerLettersFlag;
    bool endFlag;

public:
    Engine();
    ~Engine();
    void draw();
    void run();         // Runs loop with main function
    void input();


};


#endif //SCRABBLE_BR_ENGINE_H
