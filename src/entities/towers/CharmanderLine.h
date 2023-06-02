#pragma once

#include "../Tower.h"

class CharmanderTower : public Tower {
public:
  CharmanderTower(int posX, int posY);
  void upgrade() override;
};
