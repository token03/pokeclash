#include "Tower.h"
#include <cmath>
#include <iostream>

Tower::Tower(int posX, int posY) {
  radius = 10;
  position = sf::Vector2f(posX, posY);
  shape = sf::CircleShape(20);
  shape.setPosition(posX - radius, posY - radius);
  shape.setFillColor(sf::Color::Blue);
  shape.setRadius(10);
  range = 100;
}

void Tower::draw(sf::RenderWindow &window) {
  // Draw the tower itself.
  window.draw(shape);
  windowHeight = window.getSize().y;
  windowWidth = window.getSize().x;

  // Draw a circle representing the tower's range.
  sf::CircleShape rangeCircle(range);
  rangeCircle.setFillColor(sf::Color::Transparent);
  rangeCircle.setOutlineColor(sf::Color::Green);
  rangeCircle.setOutlineThickness(1.0f);

  // Position the range circle so its center is at the tower's position.
  rangeCircle.setPosition(position.x - range, position.y - range);

  window.draw(rangeCircle);
  for (Projectile &projectile : projectiles) {
    projectile.draw(window);
  }
}

bool Tower::isInRange(const Mob &mob) const {
  sf::Vector2f mobPosition = mob.getPosition();
  float distance = std::sqrt(std::pow(mobPosition.x - position.x, 2) +
                             std::pow(mobPosition.y - position.y, 2));
  return distance <= range;
}

sf::Vector2f Tower::getPosition() { return position; }

void Tower::update(float dt) {
  // Update the attack timer.
  attackTimer += dt;

  // If the attack timer has reached the attack delay, attack and reset the
  // timer.
  if (attackTimer >= attackDelay) {
    for (Mob *target : targets) {
      projectiles.push_back(Projectile(position, target, 5.0f));
    }
    attackTimer = 0.0f; // Reset the attack timer.
  }

  // Update each projectile.
  for (Projectile &projectile : projectiles) {
    if (projectile.isCollidingWithTarget()) {
      projectile.onHit();
      projectiles.erase(projectiles.begin());
    } else if (projectile.isOutOfBounds(windowHeight, windowWidth)) {
      projectiles.erase(projectiles.begin());
    } else {
      projectile.update(dt);
    }
  }
}

void Tower::addTarget(Mob *target) { targets.push_back(target); }

void Tower::clearTargets() { targets.clear(); }

bool Tower::isClicked(int x, int y) const {
  // Check if the given coordinates are within the tower's bounds.
  return x >= position.x - radius && x <= position.x + radius &&
         y >= position.y - radius && y <= position.y + radius;
}
