#pragma once

#include "Mob.h"

class Tower;
class Projectile;

enum class ProjectileType { Bullet, Beam, Column, Physical };
enum class Category { Special, Physical, Status };
enum class Effect { None, Burn, Freeze, Paralyze, Poison, Sleep };

class Move {
public:
  std::unique_ptr<Projectile> use(Mob &target, Tower &owner);
  Move(Type type, Category category, std::string name, int damage, int speed);
  Move(std::string name);
  void loadMoveData(const std::string &name);
  Type getType() const { return type; }
  int getDamage() const { return damage; }
  int getSpeed() const { return speed; }
  Category getCategory() const { return category; }
  Category mapStringToCategory(const std::string &category);
  ProjectileType getProjectileType() const { return projectileType; }
  ProjectileType mapStringToProjectileType(const std::string &projectileType);
  std::string getName() const { return name; }

private:
  std::string name;
  Category category;
  Type type;
  ProjectileType projectileType;
  int damage;
  float speed;
};
