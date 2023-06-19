#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

class PauseMenu {
public:
  PauseMenu();

  void render(sf::RenderWindow &window, bool &isPaused);
};
