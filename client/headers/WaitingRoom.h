//
// Created by erykb on 30.12.2023.
//
#ifndef SCRABBLE_BR_WAITINGROOM_H
#define SCRABBLE_BR_WAITINGROOM_H

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Player.h>
#include <Client.h>

using namespace std;
using namespace sf;



class WaitingRoom {
private:
    RenderWindow& window;
    vector<Text> playerList;
    Font font;
    string name;
    bool goBackFlag;
    bool downKeyClicked;
    sf::Color color;
    int playerCounter;
    Text text3;
    bool textflag;
    bool textflag2;
public:
    bool isGoBackFlag() const;

public:
    WaitingRoom(RenderWindow &window);
    ~WaitingRoom();
    Client client;
    vector<Player> players;
    const string &getName() const;

    void setName(const string &name);

    vector<Player> getPlayers();
    int draw(Client klajent);
};

#endif //SCRABBLE_BR_WAITINGROOM_H
