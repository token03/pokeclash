#include "UIContainer.h"

void UIContainer::draw(sf::RenderWindow &window) {
  for (UIComponent *component : components) {
    component->draw(window);
  }
}

void UIContainer::update(float dt) {
  for (UIComponent *component : components) {
    component->update(dt);
  }
}

void UIContainer::addComponent(UIComponent *component) {
  components.push_back(component);
}
