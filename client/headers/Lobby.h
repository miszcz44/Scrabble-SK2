//
// Created by erykb on 30.12.2023.
//
#ifndef SCRABBLE_BR_LOBBY_H
#define SCRABBLE_BR_LOBBY_H

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Player.h>
#include <Client.h>
#include <WaitingRoom.h>

using namespace std;
using namespace sf;


class Lobby {
private:
    RenderWindow& window;
    vector<Player> players;
    vector<Text> roomList;
    Font font;
    Client client;
    int lobbySelected;
    int roomsCounter;
    bool enterRoomFlag;
public:
    void setEnterRoomFlag(bool enterRoomFlag);
    vector<WaitingRoom> rooms;
    int flag;

private:
    WaitingRoom roomToDraw;
public:
    bool isEnterRoomFlag();

    WaitingRoom getRoomToDraw();

public:
    Lobby(RenderWindow &window);
    ~Lobby();
    bool validateNickAvailability(string nick);
    void moveUp();
    void moveDown();
    bool draw(Client client);
    void playerInput();
    void createRoom();
    void enterRoom(WaitingRoom room);
};

#endif //SCRABBLE_BR_LOBBY_H
