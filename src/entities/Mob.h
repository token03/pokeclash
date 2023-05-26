#pragma once

#include "../levels/Path.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Mob {
public:
  Mob(Path &path);                     // Constructor.
  void draw(sf::RenderWindow &window); // Draw the mob.
  sf::Vector2f getPosition() const;    // Get the mob's position.
  void update(float dt);               // Update the mob's state.
  void onHit(int damage);              // Called when the mob is hit.
  bool isDead() const;                 // Check if the mob is dead.
  int getSize() const;                 // Get the mob's size.
private:
  sf::Vector2f position;
  sf::CircleShape shape;
  Path &path;
  int currentPathPoint;
  float speed;
  int health;
  int size;
};
