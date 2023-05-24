#include "Tower.h"

Tower::Tower(int posX, int posY) {
  this->posX = posX;
  this->posY = posY;
  shape = sf::CircleShape(20);
  shape.setPosition(posX, posY);
  shape.setFillColor(sf::Color::Blue);
}

void Tower::draw(sf::RenderWindow &window) { window.draw(shape); }
