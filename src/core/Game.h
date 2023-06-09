#pragma once

#include "../entities/Mob.h"
#include "../entities/Tower.h"
#include "../entities/TowerFactory.hpp"
#include "../graphics/TextureManager.h"
#include "../levels/Level.h"
#include "../ui/PauseMenu.h"
#include "../ui/ResourceIndicator.h"
#include "../ui/SideMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>

class Game {
public:
  Game();
  ~Game();
  void run();

private:
  PauseMenu pauseMenu = PauseMenu();
  void processEvents();
  void update(float dt);
  void handleClick(sf::Vector2i position);
  void render();
  void loadTextures();
  void loadImgui();
  bool isValidPlacement(int x, int y);
  bool isPaused;
  sf::RenderWindow window;
  std::unique_ptr<ResourceIndicator> resourceIndicator;
  std::optional<SideMenu> sideMenu;
  std::unique_ptr<Level> level;
};
