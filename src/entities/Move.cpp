#include "Move.h"
#include "Projectile.h"
#include "projectiles/BeamProjectile.hpp"
#include "projectiles/BulletProjectile.hpp"
#include "projectiles/ColumnProjectile.hpp"
#include "projectiles/PhysicalProjectile.hpp"
#include <cstring>
#include <iostream>

Move::Move(Type type, Category category, std::string name, int damage,
           int speed)
    : type(type), category(category), name(name), damage(damage), speed(speed) {
}

Move::Move(std::string name) { loadMoveData(name); }

std::unique_ptr<Projectile> Move::use(Mob &target, Tower &owner) {
  // Note To Self: THIS WILL cause a memory LEAK and you SHOULD FIX IT
  auto projectile =
      std::make_unique<BulletProjectile>(target, owner, damage, speed);
  return projectile;

  switch (projectileType) {
  case ProjectileType::Bullet:
    return std::make_unique<BulletProjectile>(target, owner, damage, speed);
  case ProjectileType::Beam:
    return std::make_unique<BeamProjectile>(target, owner, damage, speed);
  case ProjectileType::Column:
    return std::make_unique<ColumnProjectile>(target, owner, damage, speed);
  case ProjectileType::Physical:
    return std::make_unique<PhysicalProjectile>(target, owner, damage, speed);
  default:
    throw std::runtime_error("Invalid ProjectileType");
  }
}

void Move::loadMoveData(const std::string &name) {
  pugi::xml_document doc;
  if (!doc.load_file("../src/data/Move.xml")) {
    throw std::runtime_error("Failed to load Move.xml");
  }

  pugi::xml_node movesNode = doc.child("Moves");
  for (pugi::xml_node moveNode = movesNode.child("Move"); moveNode;
       moveNode = moveNode.next_sibling("Move")) {
    if (moveNode.child_value("Name") == name) {
      this->name = name;
      type = TypeChecker::mapStringToType(moveNode.child_value("Type"));
      category = mapStringToCategory(moveNode.child_value("Category"));
      std::cout << moveNode.child_value("Category") << std::endl;
      projectileType =
          mapStringToProjectileType(moveNode.child_value("ProjectileType"));
      std::cout << moveNode.child_value("ProjectileType") << std::endl;
      damage = std::stoi(moveNode.child_value("Damage"));
      std::cout << moveNode.child_value("Damage") << std::endl;
      speed = (float)std::stoi(moveNode.child_value("Speed"));
      std::cout << moveNode.child_value("Speed") << std::endl;
    }
  }

  if (this->name == "") {
    throw std::runtime_error("Move not found: " + name);
  }
}

Category Move::mapStringToCategory(const std::string &category) {
  if (category == "Physical")
    return Category::Physical;
  else if (category == "Special")
    return Category::Special;
  else if (category == "Status")
    return Category::Status;
  else
    throw std::runtime_error("Invalid category: " + category);
}

ProjectileType
Move::mapStringToProjectileType(const std::string &projectileType) {
  if (projectileType == "Physical")
    return ProjectileType::Physical;
  else if (projectileType == "Beam")
    return ProjectileType::Beam;
  else if (projectileType == "Column")
    return ProjectileType::Column;
  else if (projectileType == "Bullet")
    return ProjectileType::Bullet;
  else
    throw std::runtime_error("Invalid projectile type: " + projectileType);
}
