#pragma once

#include "Mob.h"
#include "Tower.h"
#include <SFML/Graphics.hpp>

class Projectile {
public:
  Projectile(Mob &target, Tower &owner, int damage, float speed);
  void update(float dt); // Move the projectile towards the target.
  void draw(sf::RenderWindow &window);
  void onHit(); // Called when the projectile hits the target.
  bool isOutOfBounds(int windowHeight, int windowWidth) const;
  bool isCollidingWithTarget() const; // Check if the projectile is colliding.
  void setSprite(std::string key);    // Set the sprite of the projectile.

protected:
  Tower &owner; // The tower that fired this projectile.
  Mob &target;  // The mob that this projectile is moving towards.
  Type type;
  sf::Vector2f position;  // The position of the projectile.
  sf::CircleShape shape;  // The graphical representation of the projectile.
  sf::Vector2f direction; // The position of the target when the projectile
  sf::Sprite sprite;      // The graphical representation of the projectile.
  int damage;             // The amount of damage this projectile deals.
  float speed;            // The speed at which the projectile moves.
};
