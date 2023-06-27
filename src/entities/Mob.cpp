#include "Mob.h"
#include <cmath>
#include <iostream>

Mob::Mob(Path &path, std::string &name)
    : path(path), currentPathPoint(0),
      Pokemon(sf::Vector2f(path.getPoint(0).x, path.getPoint(0).y)) {
  direction = Direction::South;
  pokemon = loadPokemonData(name);
  setPokemon(pokemon);
  hp = maxHp;
  state = State::Walking;
}

void Mob::draw(sf::RenderWindow &window) {
  animations[state]->draw(window, direction);

  // Draw a circle representing the tower's radius.
  sf::CircleShape radiusCircle(hitboxRadius);
  radiusCircle.setFillColor(sf::Color::Transparent);
  radiusCircle.setOutlineColor(sf::Color::Red);
  radiusCircle.setOutlineThickness(1.0f);

  // Position the range circle so its center is at the tower's position.
  radiusCircle.setPosition(position.x - hitboxRadius,
                           position.y - hitboxRadius);

  window.draw(radiusCircle);
}

void Mob::drawHpBar(sf::RenderWindow &window) {
  // Draw the HP bar background
  sf::RectangleShape hpBackground;
  hpBackground.setSize(sf::Vector2f(50, 5)); // width and height of the HP bar
  hpBackground.setFillColor(sf::Color::Red);
  hpBackground.setOrigin(hpBackground.getSize().x / 2,
                         hpBackground.getSize().y / 2);
  hpBackground.setPosition(position.x,
                           position.y - animations[state]->getRect().height);
  hpBackground.setOutlineColor(sf::Color::Black);
  hpBackground.setOutlineThickness(1);

  window.draw(hpBackground);

  // Draw the current HP
  sf::RectangleShape currentHp;
  currentHp.setSize(sf::Vector2f(50 * (static_cast<float>(hp) / maxHp),
                                 5)); // width is proportional to the mob's HP
  currentHp.setFillColor(sf::Color::Green);
  currentHp.setOrigin(0, currentHp.getSize().y / 2);
  currentHp.setPosition(position.x - hpBackground.getSize().x / 2,
                        position.y - animations[state]->getRect().height);

  window.draw(currentHp);
}

void Mob::update(float dt) {
  if (currentPathPoint < path.getNumPoints()) {
    sf::Vector2f targetPoint = path.getPoint(currentPathPoint);
    sf::Vector2f dir =
        targetPoint - sf::Vector2f(position.x + hitboxRadius / 2,
                                   position.y + hitboxRadius / 2);
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    // Check if the mob has reached the current point
    if (distance < 1) {
      currentPathPoint++;
    } else {
      // Normalize direction vector
      dir /= distance;
      position += speed * dir * dt;
    }
    animations[state]->setPosition(position);
    direction = getDirectionToNextPoint();
    animations[state]->update(dt, direction);
  }
}

void Mob::setPokemon(PokemonData &data) {
  speed = data.mobSpeed;
  maxHp = data.mobHP;
  animations[State::Idle] =
      std::make_unique<AnimatedSprite>(data.idleAnimation);
  animations[State::Attacking] =
      std::make_unique<AnimatedSprite>(data.shootingAnimation);
  animations[State::Walking] =
      std::make_unique<AnimatedSprite>(data.walkingAnimation);
  hitboxRadius = data.hitboxRadius;
}

Direction Mob::getDirectionToNextPoint() const {
  if (currentPathPoint >= path.getNumPoints()) {
    return direction; // If no target, return current direction.
  }

  sf::Vector2f targetPosition = path.getPoint(currentPathPoint);
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

void Mob::onHit(int damage) { hp -= damage; }

bool Mob::hasReachedFinalPoint() const {
  return currentPathPoint == path.getNumPoints();
}
