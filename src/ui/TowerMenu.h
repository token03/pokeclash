#pragma once

#include "../entities/Tower.h"
#include <imgui.h>

class TowerMenu {
public:
  explicit TowerMenu(Tower *tower);
  void render();
  void toggle();
  bool isVisible() const { return visible; }

private:
  Tower *tower_;
  bool visible;
};
