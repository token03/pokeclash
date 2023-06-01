#pragma once

#include "../entities/Mob.h"
#include "../entities/Tower.h"
#include "../levels/Level.h"
#include "../ui/TowerMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <optional>

class Game {
public:
  Game();
  ~Game();
  void run();

private:
  void processEvents();
  void update(float dt);
  void handleClick(int x, int y);
  void render();
  bool isValidPlacement(int x, int y);
  bool isPaused;

private:
  sf::RenderWindow window;
  Level level;
  std::optional<TowerMenu> towerMenu_;
};
