#pragma once

#include "../entities/Mob.h"
#include "../entities/Tower.h"
#include "../entities/TowerFactory.h"
#include "../graphics/TextureManager.h"
#include "Path.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

class Level {
public:
  Level(int width, int height, TextureManager &textureManager);
  void draw(sf::RenderWindow &window);
  void update(float dt);
  void addTower(const TowerType type, int x, int y);
  void addMob();
  bool validTowerPlacement(sf::Vector2i position, int radius);
  Tower *getTowerAtPosition(int x, int y);
  int getCredits() const { return credits; }
  int getHealth() const { return health; }

private:
  int width;
  int height;
  TextureManager &textureManager;
  std::vector<std::unique_ptr<Mob>> mobs;
  std::vector<std::unique_ptr<Tower>> towers;
  Path path;
  int credits;
  int health;
  int wave;
  float mobTimer;
};
