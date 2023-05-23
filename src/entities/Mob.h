#ifndef MOB_H
#define MOB_H

#include <SFML/Graphics.hpp>

class Mob {
public:
    Mob(int posX, int posY);
    void draw(sf::RenderWindow& window);
private:
    sf::CircleShape shape;
};

#endif
