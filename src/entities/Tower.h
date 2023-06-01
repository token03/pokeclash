#pragma once

#include "Mob.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

enum class TowerStage { FIRST, SECOND, THIRD, LEGENDARY };

class Tower {
public:
  Tower(int posX, int posY);
  void draw(sf::RenderWindow &window);  // Draw the tower.
  bool isInRange(const Mob &mob) const; // Check if the mob is in range.
  bool isClicked(int x, int y) const;   // Check if the tower is clicked.
  void clearTargets();                  // Clear the tower's targets.
  void addTarget(Mob *mob);             // Add a mob to the tower's targets.
  void upgrade();                       // Upgrade the tower.
  void sell();                          // Sell the tower.
  void update(float dt);                // Update the tower's state.
  sf::Vector2f getPosition();           // Returns the tower's position.

private:
  TowerStage stage = TowerStage::FIRST;
  std::vector<Mob *> targets;
  std::vector<Projectile> projectiles;
  sf::CircleShape shape;
  sf::Vector2f position;
  float attackTimer = 0.0f, attackDelay = 0.25f;
  float range;
  float damage;
  float radius;
  int windowHeight;
  int windowWidth;
};
