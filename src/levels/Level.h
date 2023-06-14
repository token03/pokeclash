#pragma once

#include "../entities/Mob.h"
#include "../entities/MobFactory.hpp"
#include "../entities/Tower.h"
#include "../entities/TowerFactory.hpp"
#include "../graphics/TextureManager.h"
#include "Path.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Level {
public:
  Level(int width, int height);
  void draw(sf::RenderWindow &window);
  void update(float dt);
  void addTower(const PokemonType type, sf::Vector2i position);
  void sellTower(Tower *tower);
  void addMob(const PokemonType type);
  bool validTowerPlacement(sf::Vector2i position, int radius);
  Tower *getTowerAtPosition(sf::Vector2i position);
  int getCredits() const { return credits; }
  int getHealth() const { return health; }
  void setBackground();

private:
  int width;
  int height;
  std::vector<std::unique_ptr<Mob>> mobs;
  std::vector<std::unique_ptr<Tower>> towers;
  Path path;
  int credits;
  int health;
  int wave;
  float mobTimer;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
};
