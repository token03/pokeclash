#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

class Level {
public:
    Level(int width, int height);
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape tiles[20][20];  // A 20x20 grid of tiles
};

#endif

