#ifndef UICONTAINER_H
#define UICONTAINER_H

#include "UIComponent.h"

class UIContainer : public UIComponent {
public:
  void draw(sf::RenderWindow &window) override;
  void update(float dt) override;
  void addComponent(UIComponent *component);

private:
  std::vector<UIComponent *> components;
};
#endif
