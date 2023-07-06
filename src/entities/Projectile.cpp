#include "Projectile.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(Mob &target, Tower &owner, int damage, float speed)
    : target(target), speed(speed), damage(damage), owner(owner) {
  position = owner.getPosition();
  shape = sf::CircleShape(5); // Small circle shape for the projectile.
  shape.setPosition(position);
  shape.setFillColor(sf::Color::Yellow);
  direction = target.getPosition() - position;
  float length =
      std::sqrt(direction.x * direction.x + direction.y * direction.y);
  direction /= length; // Normalize the direction vector.
}

void Projectile::draw(sf::RenderWindow &window) { window.draw(shape); }

void Projectile::update(float dt) {
  // Move the projectile.
  shape.move(direction * speed);
}

bool Projectile::isOutOfBounds(int windowHeight, int windowWidth) const {
  sf::Vector2f pos = shape.getPosition();
  return pos.x < 0 || pos.y < 0 || pos.x > windowWidth || pos.y > windowHeight;
}

bool Projectile::isCollidingWithTarget() const {
  // Collision check based on distance between projectile and target center.
  // This assumes that the mob's radius is bigger than the projectile's radius.
  sf::Vector2f distanceVec = shape.getPosition() - target.getPosition();
  float distance =
      std::sqrt(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);
  return distance <= target.getSize();
}

void Projectile::onHit() { target.onHit(damage); }

void Projectile::setSprite(std::string key) {}
