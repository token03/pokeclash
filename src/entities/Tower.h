#ifndef TOWER_H
#define TOWER_H

#include "Mob.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>

class Tower {
public:
  Tower(int posX, int posY);
  void draw(sf::RenderWindow &window);  // Draw the tower.
  bool isInRange(const Mob &mob) const; // Check if the mob is in range.
  void clearTargets();                  // Clear the tower's targets.
  void addTarget(Mob *mob);             // Add a mob to the tower's targets.
  // virtual void target(const std::vector<Mob> &mobs) = 0;
  // virtual void attack(Mob &mob) = 0;
  void upgrade();        // Upgrade the tower.
  void sell();           // Sell the tower.
  void update(float dt); // Update the tower's state.

private:
  std::vector<Mob *> targets;
  std::vector<Projectile> projectiles;
  sf::CircleShape shape;
  sf::Vector2f position;
  float attackTimer = 0.0f;
  float attackDelay = 0.25f;
  float range;
  float damage;
  float size;
  int windowHeight;
  int windowWidth;
};

#endif
