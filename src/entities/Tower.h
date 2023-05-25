#ifndef TOWER_H
#define TOWER_H

#include "Mob.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>

class Tower {
public:
  Tower(int posX, int posY);
  void draw(sf::RenderWindow &window);
  bool isInRange(const Mob &mob) const;
  void clearTargets();
  void addTarget(Mob *mob);
  // virtual void target(const std::vector<Mob> &mobs) = 0;
  // virtual void attack(Mob &mob) = 0;
  void upgrade();
  void sell();
  void update();

private:
  std::vector<Mob *> targets;
  std::vector<Projectile> projectiles;
  sf::CircleShape shape;
  sf::Vector2f position;
  float range;
  float damage;
  float attackSpeed;
  float size;
};

#endif
