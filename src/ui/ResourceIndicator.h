#pragma once

#include "../levels/Level.h"
#include <SFML/Graphics.hpp>

class ResourceIndicator {
public:
  ResourceIndicator(Level &level);

  void draw(sf::RenderWindow &window);

private:
  Level &level;
  sf::Font font;
  sf::Text healthText;
  sf::Text creditsText;
};
