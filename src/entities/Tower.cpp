#include "Tower.h"
#include <cmath>
#include <iostream>

Tower::Tower(int posX, int posY) {
  state = TowerState::Idle;
  direction = Direction::South;
  position = sf::Vector2f(posX, posY);
  radius = 20;
  range = 100;
  damage = 10;
  attackDelay = 0.25f;
  attackTimer = 0.0f;
  level = 1;
  stage = TowerStage::First;
  maxTargets = 1;
  cost = 100;
  name = "Tower";
}

void Tower::draw(sf::RenderWindow &window) {
  // Draw the tower itself.
  animations[state].setPosition(position);
  animations[state].draw(window, direction);
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

  // If there are targets, set the direction to face the first target.
  if (!targets.empty()) {
    direction = getDirectionToTarget(targets[0]);
  }

  animations[state].update(dt, direction);

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

bool Tower::isClicked(sf::Vector2i clickPos) const {
  // Check if the given coordinates are within the tower's bounds.
  return clickPos.x >= position.x - radius &&
         clickPos.x <= position.x + radius &&
         clickPos.y >= position.y - radius && clickPos.y <= position.y + radius;
}

void Tower::setSprite(std::string key) {
  sprite.setTexture(TextureManager::getInstance().getRef(key));
  sprite.setPosition(position.x - sprite.getTextureRect().width / 2,
                     position.y - sprite.getTextureRect().height / 2);
}

Direction Tower::getDirectionToTarget(const Mob *target) const {
  if (!target) {
    return direction; // If no target, return current direction.
  }

  sf::Vector2f targetPosition = target->getPosition();
  float dy = targetPosition.y - position.y;
  float dx = targetPosition.x - position.x;

  float angle = std::atan2(-dy, dx);

  // Convert angle to degrees.
  angle = angle * 180.0f / 3.14159f;

  // Normalize angle to [0, 360)
  if (angle < 0.0f) {
    angle += 360.0f;
  }

  // Convert angle to a Direction. Note: This will only work well if your
  // Direction enum is set up in a way that matches these angle ranges. Adjust
  // as necessary.
  if (angle >= 337.5f || angle < 22.5f) {
    return Direction::East;
  } else if (angle >= 22.5f && angle < 67.5f) {
    return Direction::NorthEast;
  } else if (angle >= 67.5f && angle < 112.5f) {
    return Direction::North;
  } else if (angle >= 112.5f && angle < 157.5f) {
    return Direction::NorthWest;
  } else if (angle >= 157.5f && angle < 202.5f) {
    return Direction::West;
  } else if (angle >= 202.5f && angle < 247.5f) {
    return Direction::SouthWest;
  } else if (angle >= 247.5f && angle < 292.5f) {
    return Direction::South;
  } else { // angle >= 292.5f && angle < 337.5f
    return Direction::SouthEast;
  }
}

void Tower::sell() { isSold = true; }
