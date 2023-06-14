#include "BulletProjectile.h"
#include "../../graphics/TextureManager.h"

BulletProjectile::BulletProjectile(sf::Vector2f position, Mob *target,
                                   int damage, float speed)
    : Projectile(position, target, damage, speed) {
  // Change the shape and color of the projectile to be bullet-like.
  shape.setRadius(2);
  shape.setFillColor(sf::Color::Black);
  setSprite("Bullet"); // Suppose you have a "Bullet" texture loaded.
}

void BulletProjectile::onHit() {
  Projectile::onHit(); // Use base class's onHit.
  // Here you could add bullet-specific effects (like a small explosion or so).
}
