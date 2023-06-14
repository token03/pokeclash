#include "Mob.h"
#include <cmath>
#include <iostream>

Mob::Mob(Path &path, int maxHp, float speed, int size, sf::Texture &texture)
    : path(path), speed(speed), maxHp(maxHp), hp(maxHp), size(size),
      currentPathPoint(0), shape(size),
      position(
          sf::Vector2f(path.getPoint(0).x - size, path.getPoint(0).y - size)) {
  setSprite(texture);
  shape.setPosition(position);
  shape.setFillColor(sf::Color::Red);
}

void Mob::draw(sf::RenderWindow &window) { window.draw(sprite); }

void Mob::drawHpBar(sf::RenderWindow &window) {
  // Draw the HP bar background
  sf::RectangleShape hpBackground;
  hpBackground.setSize(sf::Vector2f(50, 5)); // width and height of the HP bar
  hpBackground.setFillColor(sf::Color::Red);
  hpBackground.setPosition(
      sprite.getPosition().x,
      sprite.getPosition().y -
          ((float)sprite.getTextureRect().height /
           2)); // position the HP bar 10 units above the mob sprite
  hpBackground.setOutlineColor(sf::Color::Black);
  hpBackground.setOutlineThickness(1);

  window.draw(hpBackground);

  // Draw the current HP
  sf::RectangleShape currentHp;
  currentHp.setSize(sf::Vector2f(50 * (static_cast<float>(hp) / maxHp),
                                 5)); // width is proportional to the mob's HP
  currentHp.setFillColor(sf::Color::Green);
  currentHp.setPosition(
      sprite.getPosition().x,
      sprite.getPosition().y -
          ((float)sprite.getTextureRect().height /
           2)); // position the HP bar 10 units above the mob sprite

  window.draw(currentHp);
}

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
  hp -= damage;
  std::cout << "Mob health: " << hp << std::endl;
}

bool Mob::hasReachedFinalPoint() const {
  return currentPathPoint == path.getNumPoints();
}

void Mob::setSprite(sf::Texture &texture) {
  sprite.setTexture(texture);
  sprite.setPosition(position.x - sprite.getTextureRect().width / 2.f,
                     position.y - sprite.getTextureRect().height / 2.f);
}
