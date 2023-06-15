#include "Mob.h"
#include <cmath>
#include <iostream>

Mob::Mob(Path &path, int maxHp, float speed, int size, std::string &key)
    : path(path), speed(speed), maxHp(maxHp), hp(maxHp), size(size),
      sprite(key), currentPathPoint(0), shape(size),
      position(
          sf::Vector2f(path.getPoint(0).x - size, path.getPoint(0).y - size)) {
  direction = Direction::South;
  shape.setPosition(position);
  shape.setFillColor(sf::Color::Red);
}

void Mob::draw(sf::RenderWindow &window) { sprite.draw(window, direction); }

void Mob::drawHpBar(sf::RenderWindow &window) {
  // Draw the HP bar background
  sf::RectangleShape hpBackground;
  hpBackground.setSize(sf::Vector2f(50, 5)); // width and height of the HP bar
  hpBackground.setFillColor(sf::Color::Red);
  hpBackground.setOrigin(hpBackground.getSize().x / 2,
                         hpBackground.getSize().y /
                             2); // set the origin to the center of the hp bar
  hpBackground.setPosition(
      sprite.getPosition().x,
      sprite.getPosition().y -
          sprite.getRect().height); // position the HP bar at the center and
                                    // move it above the mob sprite
  hpBackground.setOutlineColor(sf::Color::Black);
  hpBackground.setOutlineThickness(1);

  window.draw(hpBackground);

  // Draw the current HP
  sf::RectangleShape currentHp;
  currentHp.setSize(sf::Vector2f(50 * (static_cast<float>(hp) / maxHp),
                                 5)); // width is proportional to the mob's HP
  currentHp.setFillColor(sf::Color::Green);
  currentHp.setOrigin(0,
                      currentHp.getSize().y /
                          2); // set the origin to the center-left of the hp bar
  currentHp.setPosition(
      sprite.getPosition().x - hpBackground.getSize().x / 2,
      sprite.getPosition().y -
          sprite.getRect().height); // position the HP bar at the center-left
                                    // above the mob sprite

  window.draw(currentHp);
}

void Mob::update(float dt) {
  if (currentPathPoint < path.getNumPoints()) {
    sf::Vector2f targetPoint = path.getPoint(currentPathPoint);
    sf::Vector2f dir = targetPoint - position;
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    // Check if the mob has reached the current point
    if (distance < size) {
      currentPathPoint++;
    } else {
      // Normalize direction vector
      dir /= distance;
      position += speed * dir * dt;
      sprite.setPosition(position);
      direction = getDirectionToNextPoint();
      sprite.update(dt, direction);
    }
  }
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

void Mob::onHit(int damage) {
  hp -= damage;
  std::cout << "Mob health: " << hp << std::endl;
}

bool Mob::hasReachedFinalPoint() const {
  return currentPathPoint == path.getNumPoints();
}
