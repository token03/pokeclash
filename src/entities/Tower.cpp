#include "Tower.h"
#include <cmath>
#include <iostream>

Tower::Tower(int posX, int posY) {
  position = sf::Vector2f(posX, posY);
  radius = 10;
  range = 100;
  damage = 10;
  attackDelay = 0.25f;
  attackTimer = 0.0f;
  stage = TowerStage::FIRST;
  maxTargets = 1;
  cost = 100;
  name = "Tower";
}

void Tower::draw(sf::RenderWindow &window) {
  // Draw the tower itself.
  window.draw(sprite);
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

void Tower::update(float dt) {
  // Update the attack timer.
  attackTimer += dt;

  // If the attack timer has reached the attack delay, attack and reset the
  // timer.
  if (attackTimer >= attackDelay) {
    for (Mob *target : targets) {
      projectiles.emplace_back(position, target, 5.0f);
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

void Tower::addTarget(Mob *target) {
  if (targets.size() < maxTargets) {
    targets.push_back(target);
  }
}

void Tower::clearTargets() { targets.clear(); }

bool Tower::isClicked(int x, int y) const {
  // Check if the given coordinates are within the tower's bounds.
  return x >= position.x - radius && x <= position.x + radius &&
         y >= position.y - radius && y <= position.y + radius;
}

void Tower::setSprite(std::string key) {
  sprite.setTexture(TextureManager::getInstance().getRef(key));
  sprite.setPosition(position.x - sprite.getTextureRect().width / 2,
                     position.y - sprite.getTextureRect().height / 2);
}
