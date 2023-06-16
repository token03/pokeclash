#pragma once

#include "../Tower.h"

class CharmanderTower : public Tower {
public:
  CharmanderTower(sf::Vector2f position);
  int upgrade(int money) override;
};
