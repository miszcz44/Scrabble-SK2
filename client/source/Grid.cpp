#include "Grid.h"

Grid::Grid(RenderWindow &window) {
    // Init frame
    frame.setSize(Vector2f(gridSizeF * mapSize, gridSizeF * mapSize));
    frame.setPosition(25, 25);
    frame.setFillColor(Color::Transparent);
    frame.setOutlineThickness(25);
    frame.setOutlineColor(Color::Blue);
    // Init grid
    for (int x = 0; x < mapSize; x++) {
        for (int y = 0; y < mapSize; y++) {
            tiles[x][y].setSize(Vector2f(gridSizeF, gridSizeF));            // Set tile size
            tiles[x][y].setPosition(x * gridSizeF + 25,
                                    y * gridSizeF + 25);      // Adjust position based on your requirements
            tiles[x][y].setFillColor(Color::White);           // Set tile color
            tiles[x][y].setOutlineColor(Color::Black);        // Set tile outline color
            tiles[x][y].setOutlineThickness(1.f);          // Set tile outline thickness
        }
    }
    // Init letter tiles
    for (int i = 0; i < 8; i++) {
        letterTiles[i].setSize(sf::Vector2f(100, 100));
        letterTiles[i].setPosition(i * 100, 800);
        letterTiles[i].setFillColor(sf::Color::White);
        letterTiles[i].setOutlineThickness(1.f);
        letterTiles[i].setOutlineColor(sf::Color::Black);
    }
}

Grid::~Grid() = default;

void Grid::draw_grid(RenderWindow &window) {
    // Draw frame
    window.draw(frame);
    // Draw grid
    for (auto &tile: tiles)
        for (const auto & y : tile) {
            window.draw(y);
        }
    // Draw letter tiles
    for (auto &letterTile : letterTiles) {
        window.draw(letterTile);
    }
}

int Grid::getMapSize() {
    return mapSize;
}

unsigned Grid::getGridSizeU() const {
    return gridSizeU;
}

float Grid::getGridSizeF() const {
    return gridSizeF;
}

void Grid::refreshGrid(int shrinkage) {
    frame.setSize(Vector2f(gridSizeF * mapSize, gridSizeF * mapSize));
    frame.setPosition(25, 25);
    frame.setFillColor(Color::Transparent);
    frame.setOutlineThickness(25);
    frame.setOutlineColor(Color::Blue);
    // Init grid
    for (int x = 0; x < shrinkage + 1; x++) {
        for (int y = 0; y < 15; y++) {
            tiles[x][y].setSize(Vector2f(gridSizeF, gridSizeF));            // Set tile size
            tiles[x][y].setPosition(x * gridSizeF + 25,
                                    y * gridSizeF + 25);      // Adjust position based on your requirements
            tiles[x][y].setFillColor(Color::Black);           // Set tile color
            tiles[x][y].setOutlineColor(Color::Black);        // Set tile outline color
            tiles[x][y].setOutlineThickness(1.f);
            // Set tile outline thickness


            tiles[y][x].setSize(Vector2f(gridSizeF, gridSizeF));            // Set tile size
            tiles[y][x].setPosition(x * gridSizeF + 25,
                                    y * gridSizeF + 25);      // Adjust position based on your requirements
            tiles[y][x].setFillColor(Color::Black);           // Set tile color
            tiles[y][x].setOutlineColor(Color::Black);        // Set tile outline color
            tiles[y][x].setOutlineThickness(1.f);          // Set tile outline thickness

            tiles[14-x][y].setSize(Vector2f(gridSizeF, gridSizeF));            // Set tile size
            tiles[14-x][y].setPosition(x * gridSizeF + 25,
                                    y * gridSizeF + 25);      // Adjust position based on your requirements
            tiles[14-x][y].setFillColor(Color::Black);           // Set tile color
            tiles[14-x][y].setOutlineColor(Color::Black);        // Set tile outline color
            tiles[14-x][y].setOutlineThickness(1.f);          // Set tile outline thickness

            tiles[y][14-x].setSize(Vector2f(gridSizeF, gridSizeF));            // Set tile size
            tiles[y][14-x].setPosition(x * gridSizeF + 25,
                                    y * gridSizeF + 25);      // Adjust position based on your requirements
            tiles[y][14-x].setFillColor(Color::Black);           // Set tile color
            tiles[y][14-x].setOutlineColor(Color::Black);        // Set tile outline color
            tiles[y][14-x].setOutlineThickness(1.f);          // Set tile outline thickness
        }
    }
    for (int x = shrinkage+1; x < 14-shrinkage-1; x++) {
        for (int y = shrinkage+1; y < 14-shrinkage-1; y++) {
            tiles[x][y].setSize(Vector2f(gridSizeF, gridSizeF));            // Set tile size
            tiles[x][y].setPosition(x * gridSizeF + 25,
                                    y * gridSizeF + 25);      // Adjust position based on your requirements
            tiles[x][y].setFillColor(Color::White);           // Set tile color
            tiles[x][y].setOutlineColor(Color::Black);        // Set tile outline color
            tiles[x][y].setOutlineThickness(1.f);          // Set tile outline thickness
        }
    }
    // Init letter tiles
    for (int i = 0; i < 8; i++) {
        letterTiles[i].setSize(sf::Vector2f(100, 100));
        letterTiles[i].setPosition(i * 100, 800);
        letterTiles[i].setFillColor(sf::Color::White);
        letterTiles[i].setOutlineThickness(1.f);
        letterTiles[i].setOutlineColor(sf::Color::Black);
    }
}

void Grid::clear() {
    for (int x = 0; x < mapSize; x++) {
        for (int y = 0; y < mapSize; y++) {
            tiles[x][y].setSize(Vector2f(gridSizeF, gridSizeF));            // Set tile size
            tiles[x][y].setPosition(x * gridSizeF + 25,
                                    y * gridSizeF + 25);      // Adjust position based on your requirements
            tiles[x][y].setFillColor(Color::White);           // Set tile color
            tiles[x][y].setOutlineColor(Color::Black);        // Set tile outline color
            tiles[x][y].setOutlineThickness(1.f);          // Set tile outline thickness
        }
    }
}









