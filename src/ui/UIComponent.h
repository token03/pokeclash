#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class UIComponent {
public:
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void update(float dt) = 0;
};
