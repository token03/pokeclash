#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Mob.h"
#include <SFML/Graphics.hpp>

class Projectile {
public:
  Projectile(sf::Vector2f position, Mob *target, float speed);

  void update(float dt); // Move the projectile towards the target.
  void draw(sf::RenderWindow &window);

  // Add other functions as needed, e.g. to check if the projectile has hit its
  // target.

private:
  sf::CircleShape shape; // The graphical representation of the projectile.
  Mob *target;           // The mob that this projectile is moving towards.
  float speed;           // The speed at which the projectile moves.
};

#endif
