#include "MousePos.h"
#include <iostream>



MousePos::MousePos(Grid &grid) : grid(grid){
        // Initialize mouse positions
        lockedTilePos = Vector2f(-1, -1);
        // Testing values
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        font.loadFromFile("../assets/Fonts/Arialn.ttf");
        text.setFont(font);
        text.setPosition(20.f, 20.f);
        directionFlag = true;
        arrowDirection = NONE;
};

MousePos::~MousePos() = default;

void MousePos::updateMousePos(RenderWindow &window) {

    // Update mouse positions
    mousePosScreen = Mouse::getPosition();
    mousePosWindow = Mouse::getPosition(window);
    mousePosView = window.mapPixelToCoords(mousePosWindow);
    mousePosView.x -= 25;
    mousePosView.y -= 25;

    // Check if mouse coordinates are within the grid
    if (mousePosView.x >= 0.f) {
        mousePosGrid.x = mousePosView.x / grid.getGridSizeU();
    }
    if (mousePosView.y >= 0.f) {
        mousePosGrid.y = mousePosView.y / grid.getGridSizeU();
    }

}



void MousePos::initTileSelector(RenderWindow &window) {
    tileSelector.setSize(Vector2f(grid.getGridSizeF(), grid.getGridSizeF()));
    tileSelector.setFillColor(Color::Transparent);
    tileSelector.setOutlineThickness(2.f);
    tileSelector.setOutlineColor(Color::Red);

}

void MousePos::updateTileSelector(RenderWindow &window) {

    if (mousePosGrid.x >= 0 && mousePosGrid.x < grid.getMapSize()
    && mousePosGrid.y >= 0 && mousePosGrid.y < grid.getMapSize()) {
        if (tileLocked) {
            tileSelector.setPosition(lockedTilePos.x * grid.getGridSizeF() + 25,
                                     lockedTilePos.y * grid.getGridSizeF() + 25);
            tileSelector.setOutlineColor(Color::Green);
        } else {
            tileSelector.setPosition(mousePosGrid.x * grid.getGridSizeF() + 25,
                                     mousePosGrid.y * grid.getGridSizeF() + 25);
            tileSelector.setOutlineColor(Color::Red);
        }
    }
    // Adjust tile selector position for grid offset
    window.draw(tileSelector);
}

void MousePos::handleMouseClick(RenderWindow &window, array<array<char, 15>, 15> gameState, vector<Vector2f> playerPositions) {
    if (Mouse::isButtonPressed(Mouse::Left) && directionFlag) {
        if (mousePosGrid.x >= 0 && mousePosGrid.x < grid.getMapSize()
        && mousePosGrid.y >= 0 && mousePosGrid.y < grid.getMapSize()
        && gameState[mousePosGrid.x][mousePosGrid.y] != '0'
        && gameState[mousePosGrid.x][mousePosGrid.y] != '!'
        && find(dangerZones.begin(), dangerZones.end(), Vector2f(mousePosGrid.x, mousePosGrid.y)) ==
           dangerZones.end()
       && find(playerPositions.begin(), playerPositions.end(), Vector2f(mousePosGrid.x, mousePosGrid.y)) !=
          playerPositions.end()) {
            if (!tileLocked) {
                tileLocked = true;
                lockedTilePos = Vector2f(mousePosGrid);
                // Initialize the arrow
                arrow.setPointCount(3);
                arrow.setPoint(0, Vector2f(0, 0));
                arrow.setPoint(1, Vector2f(grid.getGridSizeF() / 2, grid.getGridSizeF()));
                arrow.setPoint(2, Vector2f(grid.getGridSizeF(), 0));
                arrow.setOrigin(grid.getGridSizeF() / 2, grid.getGridSizeF() / 2);
                arrow.setFillColor(Color::Green);
                arrow.setOutlineColor(Color::Blue);
                arrow.setOutlineThickness(3);
                arrow.setScale(0.5f, 0.5f);
            } else if (sf::Vector2f(mousePosGrid) == lockedTilePos) {
                tileLocked = false;
                lockedTilePos = Vector2f(-1, -1);
            }
        }
        sleep(milliseconds(100));
    }
}

void MousePos::handleArrowKeys() {
    if(directionFlag) {
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            arrowDirection = UP;
        } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            arrowDirection = DOWN;
        } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            arrowDirection = LEFT;
        } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            arrowDirection = RIGHT;
        }
    }
}

void MousePos::drawArrow(RenderWindow &window) {
    if (tileLocked && arrowDirection != NONE) {
        // Check if the arrow is pointing outside the grid
        if (!checkArrowPos()) {
            return;
        }

        // Calculate the position of the arrow based on the position of the locked tile and the direction of the arrow
        Vector2f arrowPos = lockedTilePos * grid.getGridSizeF();
        switch (arrowDirection) {
            case UP:
                arrow.setRotation(180);
                arrowPos.y -= grid.getGridSizeF() / 3 - 25;
                arrowPos.x += grid.getGridSizeF() / 2 + 25;
                break;
            case DOWN:
                arrow.setRotation(0);
                arrowPos.y += grid.getGridSizeF() * 1.3 + 25;
                arrowPos.x += grid.getGridSizeF() / 2 + 25;
                break;
            case LEFT:
                arrow.setRotation(90);
                arrowPos.x -= grid.getGridSizeF() / 3 - 25;
                arrowPos.y += grid.getGridSizeF() / 2 + 25;
                break;
            case RIGHT:
                arrow.setRotation(270);
                arrowPos.x += grid.getGridSizeF() * 1.3 + 25;
                arrowPos.y += grid.getGridSizeF() / 2 + 25;
                break;
            case NONE:
                break;
        }

        // Set the position of the arrow and draw it
        arrow.setPosition(arrowPos);
        window.draw(arrow);
    }
}


bool MousePos::checkArrowPos() {
    switch (arrowDirection) {
        case UP:
            if (lockedTilePos.y <= 0) {
                return false;
            }
            break;
        case DOWN:
            if (lockedTilePos.y >= grid.getMapSize() - 1) {
                return false;
            }
            break;
        case LEFT:
            if (lockedTilePos.x <= 0) {
                return false;
            }
            break;
        case RIGHT:
            if (lockedTilePos.x >= grid.getMapSize() - 1) {
                return false;
            }
            break;
    }
    return true;
}

Font MousePos::getFont() {
    return font;
}

Vector2f MousePos::getLockedTilePos() {
    return lockedTilePos;
}

MousePos::Direction MousePos::getArrowDirection() const {
    return arrowDirection;
}

void MousePos::setDangerZones(vector<Vector2f> zones) {
    dangerZones = zones;
}

void MousePos::clear() {
    directionFlag = true;
    arrowDirection = NONE;
    lockedTilePos = Vector2f(-1, -1);
    dangerZones.clear();
}

