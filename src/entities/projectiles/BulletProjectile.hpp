#pragma once
#include "../Projectile.h"

class BulletProjectile : public Projectile {
public:
  BulletProjectile(Mob &target, Tower &owner, int damage, float speed)
      : Projectile(target, owner, damage, speed) {
    // Change the shape and color of the projectile to be bullet-like.
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Black);
    setSprite("Bullet"); // Suppose you have a "Bullet" texture loaded.
  }

  void onHit() {
    Projectile::onHit(); // Use base class's onHit.
    // Here you could add bullet-specific effects (like a small explosion or
    // so).
  }

  void update(float dt) {
    // Move the projectile.
    shape.move(direction * speed);
  }
};
