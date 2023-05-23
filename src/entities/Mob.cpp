#include "Mob.h"

Mob::Mob(int posX, int posY) {
    shape = sf::CircleShape(10.f);
    shape.setPosition(posX, posY);
    shape.setFillColor(sf::Color::Red);
}

void Mob::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
