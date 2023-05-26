#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <SFML/Graphics/RenderWindow.hpp>

class UIComponent {
public:
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void update(float dt) = 0;
};

#endif
