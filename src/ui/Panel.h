#ifndef PANEL_H
#define PANEL_H

#include "UIComponent.h"

class Panel : public UIComponent {
public:
  Panel(float x, float y, float width, float height);
  void draw(sf::RenderWindow &window) override;
  void update(float dt) override;
  void addComponent(UIComponent &component);
  // Other panel-specific methods...
};

#endif
