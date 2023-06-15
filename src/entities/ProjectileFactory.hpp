#pragma once

#include "Mob.h"
#include "Projectile.h"
#include "Tower.h"
#include "projectiles/BulletProjectile.hpp"
#include <memory>
#include <vector>

enum class ProjectileType {
  BeamProjectile,
  BulletProjectile,
};

class ProjectileFactory {
public:
  static std::unique_ptr<Projectile> createProjectile(const ProjectileType type,
                                                      sf::Vector2f position,
                                                      Mob *target, int damage,
                                                      float speed) {
    if (type == ProjectileType::BulletProjectile) {
      return std::make_unique<BulletProjectile>(position, target, damage,
                                                speed);
    } else {
      throw std::invalid_argument("Invalid tower type");
    }
  }
};
