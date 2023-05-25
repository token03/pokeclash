#include "Projectile.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f position, Mob *target, float speed)
    : target(target), speed(speed) {
  shape.setPosition(position);
  shape.setRadius(5);                  // For example, set the radius to 5.
  shape.setFillColor(sf::Color::Blue); // For example, set the color to blue.
}

void Projectile::update() {
  // Calculate the direction to the target.
  sf::Vector2f direction = target->getPosition() - shape.getPosition();
  // Normalize the direction vector (give it a length of 1).
  float length =
      std::sqrt(direction.x * direction.x + direction.y * direction.y);
  direction /= length;
  // Move the projectile in the direction of the target.
  shape.move(direction * speed);
}

void Projectile::draw(sf::RenderWindow &window) { window.draw(shape); }
