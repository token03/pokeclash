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

class SideMenu {
public:
  SideMenu(sf::RenderWindow &window, std::unique_ptr<Level> &level);
  void render();
  void setSelectedTower(Tower *tower);
  Tower *getSelectedTower();
  void resetCurrentPokemonToPlace();
  std::optional<PokemonType> getCurrentPokemonToPlace();
  void reset();

private:
  void renderTowerPlacement();
  void renderTowerManagement();
  void renderStats();
  sf::RenderWindow &window;
  std::unique_ptr<Level> &level;
  std::optional<PokemonType> currentPokemonToPlace;
  Tower *selectedTower = nullptr;
};
