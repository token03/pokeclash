#include "Tower.h"

Tower::Tower(int posX, int posY) {
    shape = sf::RectangleShape(sf::Vector2f(20.f, 20.f));
    shape.setPosition(posX, posY);
    shape.setFillColor(sf::Color::Blue);
}

void Tower::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
