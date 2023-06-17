#pragma once

#include "../entities/Tower.h"
#include "../entities/TowerFactory.hpp"
#include "../levels/Level.h"
#include "../ui/TowerMenu.h"
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

private:
  void renderTowerPlacement();
  void renderTowerManagement();
  void renderStats();
  sf::RenderWindow &window;
  std::unique_ptr<Level> &level;
  std::optional<TowerMenu> towerMenu_;
  std::optional<PokemonType> currentPokemonToPlace;
  Tower *selectedTower = nullptr;
};
