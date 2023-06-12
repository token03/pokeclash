#include "Mob.h"
#include <cmath>
#include <iostream>

Mob::Mob(Path &path, int health, float speed, int size, sf::Texture &texture)
    : path(path), speed(speed), health(health), size(size), currentPathPoint(0),
      shape(size), position(sf::Vector2f(path.getPoint(0).x - size,
                                         path.getPoint(0).y - size)) {
  setSprite(texture);
  shape.setPosition(position);
  shape.setFillColor(sf::Color::Red);
}

void Mob::draw(sf::RenderWindow &window) { window.draw(sprite); }

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
      sprite.setPosition(position);
    }
  }
}

void Mob::onHit(int damage) {
  health -= damage;
  std::cout << "Mob health: " << health << std::endl;
}

bool Mob::hasReachedFinalPoint() const {
  return currentPathPoint == path.getNumPoints();
}

void Mob::setSprite(sf::Texture &texture) {
  sprite.setTexture(texture);
  sprite.setPosition(position.x - sprite.getTextureRect().width / 2.f,
                     position.y - sprite.getTextureRect().height / 2.f);
}
