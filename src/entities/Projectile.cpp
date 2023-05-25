#include "Projectile.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f position, Mob *target, float speed)
    : target(target), speed(speed) {
  shape = sf::CircleShape(5); // Small circle shape for the projectile.
  shape.setPosition(position);
  shape.setFillColor(
      sf::Color::Yellow); // For visibility, set the color to yellow.
}

void Projectile::update() {
  if (target != nullptr) {
    // Calculate direction to the target.
    sf::Vector2f direction = target->getPosition() - shape.getPosition();
    float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // Normalize the direction vector.

    // Move the projectile.
    shape.move(direction * speed);
  }
}

void Projectile::draw(sf::RenderWindow &window) { window.draw(shape); }
