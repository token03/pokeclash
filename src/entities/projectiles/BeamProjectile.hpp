#pragma once
#include "../Projectile.h"
#include <cmath>
#include <iostream>

class BeamProjectile : public Projectile {
public:
  BeamProjectile(Mob &target, Tower &owner, int damage, float speed)
      : Projectile(target, owner, damage, speed) {
    beam = sf::RectangleShape(sf::Vector2f(20, 100)); // width, length
    beam.setFillColor(sf::Color::Red);
  }

  void update(float dt) override {
    // Always position the beam so that it starts from the tower and points
    // towards the target.
    position = owner.getPosition();
    direction = target.getPosition() - position;
    float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // Normalize the direction vector.

    // Set the beam's position and rotation.
    beam.setSize(sf::Vector2f(20, length));
    beam.setPosition(position);
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;
    beam.setRotation(angle - 90);
  }

  bool isOutOfBounds(int windowHeight, int windowWidth) const {
    // Beam is never out of bounds since it always starts from the tower.
    return false;
  }

  bool isCollidingWithTarget() const override {
    // Beam is always colliding with the target since it always points towards
    // the target.
    return false;
  }

  void onHit() override {
    // Damage the target every time onHit is called.
    // The game loop needs to call this method frequently to mimic the
    // continuous damage effect of a beam.
    target.onHit(damage);
  }

  void draw(sf::RenderWindow &window) override {
    // Draw the beam.
    window.draw(beam);
  }

private:
  sf::RectangleShape beam;
};
