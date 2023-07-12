#pragma once

#include "../entities/Mob.h"
#include "../entities/MobFactory.hpp"
#include "../entities/Pokemon.h"
#include "../entities/Tower.h"
#include "../entities/TowerFactory.hpp"
#include "../entities/Type.hpp"
#include "../graphics/TextureManager.h"
#include "Path.h"
#include "Wave.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Level {
public:
  Level(int width, int height);
  void draw(sf::RenderWindow &window);
  void update(float dt);
  void updateWave(float dt);
  void updateMobs(float dt);
  void updateTowers(float dt);
  void updateProjectiles(float dt);
  void addTower(const std::string &pokemon, sf::Vector2f position);
  void sellTower(Tower *tower);
  void addMob(const std::string &pokemon);
  bool validTowerPlacement(sf::Vector2f position, int radius);
  Tower *getTowerAtPosition(sf::Vector2f position);
  int getCredits() const { return credits; }
  int getHealth() const { return health; }
  int getCurrentWave() const { return wave; }
  void setBackground();

private:
  int width;
  int height;
  std::vector<std::unique_ptr<Mob>> mobs;
  std::vector<std::unique_ptr<Tower>> towers;
  std::vector<std::unique_ptr<Projectile>> projectiles;
  Path path;
  std::vector<Wave> waves;
  int credits;
  int health;
  int wave;
  float mobTimer;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
};
