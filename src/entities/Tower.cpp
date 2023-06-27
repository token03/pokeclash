#include "Tower.h"
#include <cmath>
#include <iostream>

Tower::Tower(const std::string &name, sf::Vector2f position)
    : Pokemon(position) {
  pokemon = loadPokemonData(name);
  setPokemon(pokemon);
  state = State::Idle;
  direction = Direction::South;
  stage = TowerStage::First;
  level = 1;
  maxTargets = 1;
}

void Tower::setPokemon(PokemonData &data) {
  name = data.name;
  baseRange = data.towerBaseRange;
  baseDamage = data.towerBaseDamage;
  attackDelay = 1.0f / data.towerAttacksPerSecond;
  attackTimer = 0.0f;
  animations[State::Idle] =
      std::make_unique<AnimatedSprite>(data.idleAnimation);
  animations[State::Attacking] =
      std::make_unique<AnimatedSprite>(data.shootingAnimation);
  animations[State::Attacking]->setAttackSpeed(data.towerAttacksPerSecond);
  range = baseRange;
  damage = baseDamage;
  hitboxRadius = data.hitboxRadius;
  cost = data.towerCost;
  upgradeCost = 1;
}

void Tower::draw(sf::RenderWindow &window) {
  // Draw the tower itself.
  animations[state]->setPosition(position);
  animations[state]->draw(window, direction);
  windowHeight = window.getSize().y;
  windowWidth = window.getSize().x;

  // Draw a circle representing the tower's range.
  sf::CircleShape rangeCircle(range);
  rangeCircle.setFillColor(sf::Color::Transparent);
  rangeCircle.setOutlineColor(sf::Color::Green);
  rangeCircle.setOutlineThickness(1.0f);

  // Draw a circle representing the tower's radius.
  sf::CircleShape radiusCircle(hitboxRadius);
  radiusCircle.setFillColor(sf::Color::Transparent);
  radiusCircle.setOutlineColor(sf::Color::Red);
  radiusCircle.setOutlineThickness(1.0f);

  // Position the range circle so its center is at the tower's position.
  rangeCircle.setPosition(position.x - range, position.y - range);
  radiusCircle.setPosition(position.x - hitboxRadius,
                           position.y - hitboxRadius);

  window.draw(rangeCircle);
  window.draw(radiusCircle);

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
    state = State::Attacking;
  } else {
    state = State::Idle;
    direction = Direction::South;
  }

  animations[state]->update(dt, direction);

  if (attackTimer >= attackDelay) {
    for (Mob *target : targets) {
      projectiles.emplace_back(position, target, damage, 10.0f);
    }
    attackTimer = 0.0f; // Reset the attack timer.
  }

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

int Tower::upgrade(int money) {
  if (money < upgradeCost || level == 100)
    return 0;

  level++;
  damage += 5;
  std::cout << "Evolution Level: " << pokemon.evolutionLevel << std::endl;

  if (level >= pokemon.evolutionLevel && pokemon.evolutionName != "") {
    std::string name = pokemon.evolutionName;
    std::cout << name << std::endl;
    pokemon = loadPokemonData(name);
    setPokemon(pokemon);
  }

  return upgradeCost;
}
void Tower::addTarget(Mob *target) {
  if (targets.size() < maxTargets) {
    targets.push_back(target);
  }
}

void Tower::clearTargets() { targets.clear(); }

bool Tower::isClicked(sf::Vector2f clickPos) const {
  // Check if the given coordinates are within the tower's bounds.
  return clickPos.x >= position.x - hitboxRadius &&
         clickPos.x <= position.x + hitboxRadius &&
         clickPos.y >= position.y - hitboxRadius &&
         clickPos.y <= position.y + hitboxRadius;
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
