#include "Mob.h"

Mob::Mob(float posX, float posY) { // change int to float here
  shape = sf::CircleShape(10.f);
  shape.setPosition(posX, posY);
  position = sf::Vector2f(posX - 10, posY - 10);
  shape.setFillColor(sf::Color::Red);
}

sf::Vector2f Mob::getPosition() const { return shape.getPosition(); }

void Mob::draw(sf::RenderWindow &window) { window.draw(shape); }

void Mob::update(float dt) {
  position.x += 0.1f;
  shape.setPosition(position);
}
