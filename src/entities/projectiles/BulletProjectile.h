#pragma once
#include "../Projectile.h"

class BulletProjectile : public Projectile {
public:
  BulletProjectile(sf::Vector2f position, Mob *target, int damage, float speed);
  void onHit() override;
};
