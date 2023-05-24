#ifndef GAME_H
#define GAME_H

#include "../entities/Mob.h"
#include "../entities/Tower.h"
#include "../levels/Level.h"
#include <SFML/Graphics.hpp>

class Game {
public:
  Game();
  void run();

private:
  void processEvents();
  void update();
  void render();
  bool isValidPlacement(int x, int y);

private:
  sf::RenderWindow window;
  Level level;
};

#endif
