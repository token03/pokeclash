#pragma once
#include "../graphics/AnimatedSprite.h"

class Pokemon {
public:
  Pokemon(sf::Vector2f pos);
  sf::Vector2f getPosition() const { return position; }
  Direction getDirection() const { return direction; }
  void setPosition(const sf::Vector2f &pos);
  void setDirection(Direction dir) { direction = dir; }
  void draw(sf::RenderWindow &window);
  void update(float dt);

protected:
  sf::Vector2f position;
  Direction direction;
};
