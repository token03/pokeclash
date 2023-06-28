#include "Move.h"
#include <cstring>

Move::Move(Type type, Category category, std::string name, int damage,
           int speed)
    : type(type), category(category), name(name), damage(damage), speed(speed) {
}

std::unique_ptr<Projectile> Move::use(Mob *target, sf::Vector2f position) {
  // Note To Self: THIS WILL cause a memory LEAK and you SHOULD FIX IT
  auto projectile =
      std::make_unique<Projectile>(position, target, damage, speed);
  return projectile;
}

void Move::loadMoveData(const std::string &name) {
  pugi::xml_document doc;
  if (!doc.load_file("../src/data/Move.xml")) {
    throw std::runtime_error("Failed to load Move.xml");
  }

  pugi::xml_node movesNode = doc.child("Moves");
  for (pugi::xml_node moveNode = movesNode.child("Move"); moveNode;
       moveNode = moveNode.next_sibling("Pokemon")) {
    if (moveNode.child_value("Name") == name) {
      PokemonData data;
      this->name = name;
      type = TypeChecker::mapStringToType(moveNode.child_value("Type"));
      category = mapStringToCategory(moveNode.child_value("Category"));
      damage = std::stoi(moveNode.child_value("Damage"));
      speed = std::stoi(moveNode.child_value("Speed"));
    }
  }

  throw std::runtime_error("Pokemon not found: " + name);
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

ProjectileType mapStringToProjectileType(const std::string &projectileType) {
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
