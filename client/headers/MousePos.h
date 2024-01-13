#ifndef SCRABBLE_BR_MOUSEPOS_H
#define SCRABBLE_BR_MOUSEPOS_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include "Grid.h"
#include <sstream>
using namespace std;
using namespace sf;

class MousePos {
private:
    Text text;  // Show the mouse position
    Font font;

    //  Mouse position variables
    Vector2i mousePosScreen;
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    Vector2u mousePosGrid;
    vector<Vector2f> dangerZones;
    // Tile selector lock variables
    bool tileLocked = false;
    // Tile selector arrow variables
    ConvexShape arrow;

    // References
    Grid &grid;
    RectangleShape tileSelector;

public:
    explicit MousePos(Grid& grid);
    ~MousePos();

    Vector2f lockedTilePos;
    enum Direction { UP, DOWN, LEFT, RIGHT, NONE};
    Direction arrowDirection;
    bool directionFlag;
    void updateMousePos(RenderWindow &window);
    void initTileSelector(RenderWindow &window);
    void updateTileSelector(RenderWindow &window);
    void handleMouseClick(RenderWindow &window, array<array<char, 15>, 15>, vector<Vector2f> playerPositions);
    void handleArrowKeys();
    void drawArrow(RenderWindow &window);
    bool checkArrowPos();
    void clear();
    Vector2f getLockedTilePos();
    Font getFont();
    void setDangerZones(vector<Vector2f> zones);
    Direction getArrowDirection() const;
};


#endif //SCRABBLE_BR_MOUSEPOS_H
