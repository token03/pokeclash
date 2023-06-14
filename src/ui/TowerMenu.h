#pragma once

#include "../entities/Tower.h"
#include "../levels/Level.h"
#include <imgui.h>

class TowerMenu {
public:
  explicit TowerMenu(Tower *tower, Level *level);
  void render();
  void toggle();
  bool isVisible() const { return visible; }
  void setTower(Tower *tower);

private:
  Tower *tower_;
  Level *level_;
  bool visible;
};
