#pragma once

#include "../entities/Mob.h"
#include "../entities/Tower.h"
#include "../entities/TowerFactory.h"
#include "Path.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Level {
public:
  Level(int width, int height);
  void draw(sf::RenderWindow &window);
  void update(float dt);
  void addTower(const std::string &type, int x, int y);
  bool validTowerPlacement(sf::Vector2i position, int radius);
  Tower *getTowerAtPosition(int x, int y);

private:
  int width;
  int height;
  std::vector<std::unique_ptr<Mob>> mobs;
  std::vector<std::unique_ptr<Tower>> towers;
  Path path;
};
