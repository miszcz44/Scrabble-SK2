#ifndef SCRABBLE_BR_GRID_H
#define SCRABBLE_BR_GRID_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace std;
using namespace sf;

class Grid {
private:
    float viewSpeed = 100.f;
    static const int mapSize = 15;
    float gridSizeF = 50.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);


public:
    explicit Grid(RenderWindow &window);
    ~Grid();
    RectangleShape tiles[mapSize][mapSize];
    RectangleShape frame;
    RectangleShape letterTiles[8];

    void draw_grid(RenderWindow &window);
    void clear();
    static int getMapSize() ;
    unsigned getGridSizeU() const;
    float getGridSizeF() const;
    void refreshGrid(int shrinkage);
};


#endif //SCRABBLE_BR_GRID_H
