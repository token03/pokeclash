#include "Mob.h"
#include <cmath>
#include <iostream>

Mob::Mob(Path &path) : path(path), currentPathPoint(0) {
  size = 10;
  health = 100;
  speed = 20.0f;
  shape = sf::CircleShape(size);
  position = sf::Vector2f(path.getPoint(0).x - size, path.getPoint(0).y - size);
  std::cout << path.getPoint(0).x << std::endl;
  shape.setPosition(position);
  shape.setFillColor(sf::Color::Red);
}

sf::Vector2f Mob::getPosition() const { return position; }

int Mob::getSize() const { return size; }

void Mob::draw(sf::RenderWindow &window) { window.draw(shape); }

void Mob::update(float dt) {
  if (currentPathPoint < path.getNumPoints()) {
    sf::Vector2f targetPoint = path.getPoint(currentPathPoint);
    sf::Vector2f direction = targetPoint - position;
    float distance =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Check if the mob has reached the current point
    if (distance < size) {
      currentPathPoint++;
    } else {
      // Normalize direction vector
      direction /= distance;
      position += speed * direction * dt;
      shape.setPosition(position);
    }
  }
}
void Mob::onHit(int damage) {
  health -= damage;
  std::cout << "Mob health: " << health << std::endl;
}

bool Mob::isDead() const { return health <= 0; }
