#pragma once

#include "../entities/Tower.h"
#include <imgui.h>

class TowerMenu {
public:
  explicit TowerMenu(Tower *tower);
  void render();

private:
  Tower *tower_;
};
