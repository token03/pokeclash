#include "Move.h"

Move::Move(Type type, Category category, std::string name, int damage,
           int speed)
    : type(type), category(category), name(name), damage(damage), speed(speed) {
}

std::unique_ptr<Projectile> Move::use(Mob &target, Tower &tower) {
  // Note To Self: THIS WILL cause a memory LEAK and you SHOULD FIX IT
  auto projectile =
      std::make_unique<Projectile>(tower.getPosition(), &target, damage, speed);
  return projectile;
}
