#ifndef BUTTON_H
#define BUTTON_H

#include "UIComponent.h"

class Button : public UIComponent {
public:
  Button(float x, float y, float width, float height);
  void draw(sf::RenderWindow &window) override;
  void update(float dt) override;
  // Other button-specific methods...
};

#endif
