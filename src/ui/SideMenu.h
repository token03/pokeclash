#pragma once

#include "../entities/Tower.h"
#include "../entities/TowerFactory.hpp"
#include "../levels/Level.h"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>

using std::string;

class SideMenu {
public:
  SideMenu(sf::RenderWindow &window, std::unique_ptr<Level> &level);
  void render();
  void setSelectedTower(Tower *tower);
  Tower *getSelectedTower();
  void resetCurrentPokemonToPlace();
  std::optional<string> getCurrentPokemonToPlace();
  void reset();

private:
  void renderTowerPlacement();
  void renderTowerManagement();
  void renderStats();
  sf::RenderWindow &window;
  std::unique_ptr<Level> &level;
  std::optional<string> currentPokemonToPlace;
  Tower *selectedTower = nullptr;
};
