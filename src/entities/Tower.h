#ifndef TOWER_H
#define TOWER_H

#include "Mob.h"
#include <SFML/Graphics.hpp>

class Tower {
public:
  Tower(int posX, int posY);
  void draw(sf::RenderWindow &window);
  bool isInRange(const Mob &mob) const;
  // virtual void target(const std::vector<Mob> &mobs) = 0;
  // virtual void attack(Mob &mob) = 0;
  void upgrade();
  void sell();

private:
  sf::CircleShape shape;
  int posX;
  int posY;
  float range;
  float damage;
  float attackSpeed;
  float size;
};

#endif
