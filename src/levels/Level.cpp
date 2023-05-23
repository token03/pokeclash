#include "Level.h"

Level::Level(int width, int height) {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            tiles[i][j] = sf::RectangleShape(sf::Vector2f(width, height));
            tiles[i][j].setPosition(i * width, j * height);
            tiles[i][j].setFillColor(sf::Color(245, 222, 179));  // Wheat color
            tiles[i][j].setOutlineThickness(-1.0f); // Negative values will draw the outline inside the shape
            tiles[i][j].setOutlineColor(sf::Color::Black); // Set the outline color to black
        }
    }
}

void Level::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            window.draw(tiles[i][j]);
        }
    }
}
