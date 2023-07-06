#pragma once
#include "../Projectile.h"

class BeamProjectile : public Projectile {
public:
  BeamProjectile(Mob &target, Tower &owner, int damage, float speed)
      : Projectile(target, owner, damage, speed) {
    // Change the shape and color of the projectile to be bullet-like.
    shape.setRadius(2);
    shape.setFillColor(sf::Color::Black);
    setSprite("Bullet"); // Suppose you have a "Bullet" texture loaded.
  }

  void onHit() {
    Projectile::onHit(); // Use base class's onHit.
    // Here you could add bullet-specific effects (like a small explosion or
    // so).
  }
};
