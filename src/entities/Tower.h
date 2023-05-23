#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>

class Tower {
public:
    Tower(int posX, int posY);
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape shape;
};

#endif
