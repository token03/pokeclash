#pragma once

#include "Projectile.h"
#include "Tower.h"

enum class Category { Special, Physical, Status };

class Move {
public:
  std::unique_ptr<Projectile> use(Mob &target, Tower &tower);
  Move(Type type, Category category, std::string name, int damage, int speed);
  Type getType() const { return type; }
  int getDamage() const { return damage; }
  int getSpeed() const { return speed; }
  Category getCategory() const { return category; }

private:
  std::string name;
  Category category;
  Type type;
  int damage;
  float speed;
};
