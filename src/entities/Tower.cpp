#include "Tower.h"
#include <cmath>

Tower::Tower(int posX, int posY) {
  position = sf::Vector2f(posX, posY);
  shape = sf::CircleShape(20);
  shape.setPosition(posX, posY);
  shape.setFillColor(sf::Color::Blue);
}

void Tower::draw(sf::RenderWindow &window) { window.draw(shape); }

bool Tower::isInRange(const Mob &mob) const {
  sf::Vector2f mobPosition = mob.getPosition();
  float distance = std::sqrt(std::pow(mobPosition.x - position.x, 2) +
                             std::pow(mobPosition.y - position.y, 2));
  return distance <= range;
}

void Tower::update() {
  for (Mob *target : targets) {
    // Fire a projectile at the target. The projectile's speed is 1.0f, but you
    // can change this.
    projectiles.push_back(Projectile(position, target, 1.0f));
  }

  // Update each projectile.
  for (Projectile &projectile : projectiles) {
    projectile.update();
  }
}
void Tower::addTarget(Mob *target) { targets.push_back(target); }

void Tower::clearTargets() { targets.clear(); }
