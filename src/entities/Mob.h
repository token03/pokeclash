#pragma once

#include "../graphics/TextureManager.h"
#include "../levels/Path.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Mob {
public:
  Mob(Path &path, int health, float speed, int size, sf::Texture &texture);
  void draw(sf::RenderWindow &window);                  // Draw the mob.
  sf::Vector2f getPosition() const { return position; } // Get position.
  void update(float dt);                      // Update the mob's state.
  bool isDead() const { return health <= 0; } // Check if the mob is dead.
  void onHit(int damage);                     // Called when the mob is hit.
  int getSize() const { return size; }        // Get the mob's size.
  bool hasReachedFinalPoint() const;    // Check if the mob has reached the end.
  void setSprite(sf::Texture &texture); // Set the mob's sprite.
private:
  sf::Vector2f position;
  sf::CircleShape shape;
  Path &path;
  int currentPathPoint;
  float speed;
  int health;
  int size;
  sf::Sprite sprite;
};
