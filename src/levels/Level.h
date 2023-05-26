#ifndef LEVEL_H
#define LEVEL_H

#include "../entities/Mob.h"
#include "../entities/Tower.h"
#include "Path.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Level {
public:
  Level(int width, int height);
  void draw(sf::RenderWindow &window);
  void update(float dt);
  void addTower(int x, int y);
  bool validTowerPlacement(sf::Vector2i position, int radius);

private:
  int width;
  int height;
  std::vector<std::unique_ptr<Mob>> mobs;
  std::vector<Tower> towers;
  Path path;
};

#endif
