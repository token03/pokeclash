#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Mob.h"
#include <SFML/Graphics.hpp>

class Projectile {
public:
  Projectile(sf::Vector2f position, Mob *target, float speed);
  void update(float dt); // Move the projectile towards the target.
  void draw(sf::RenderWindow &window);
  void onHit(); // Called when the projectile hits the target.
  bool isOutOfBounds(int windowHeight, int windowWidth) const;
  bool isCollidingWithTarget()
      const; // Check if the projectile is colliding with the target.

private:
  sf::CircleShape shape;  // The graphical representation of the projectile.
  Mob *target;            // The mob that this projectile is moving towards.
  int damage;             // The amount of damage this projectile deals.
  float speed;            // The speed at which the projectile moves.
  sf::Vector2f direction; // The position of the target when the projectile
};

#endif
