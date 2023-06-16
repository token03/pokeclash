#pragma once

#include "../graphics/AnimatedSprite.h"
#include "../graphics/TextureManager.h"
#include "../levels/Path.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Mob {
public:
  Mob(Path &path, int maxHp, float speed, float size,
      std::string &animationKey);
  void draw(sf::RenderWindow &window);      // Draw the mob.
  void drawHpBar(sf::RenderWindow &window); // Draw the mob's HP bar.
  sf::Vector2f getPosition() const { return position; } // Get position.
  void update(float dt);                  // Update the mob's state.
  bool isDead() const { return hp <= 0; } // Check if the mob is dead.
  void onHit(int damage);                 // Called when the mob is hit.
  int getSize() const { return size; }    // Get the mob's size.
  bool hasReachedFinalPoint() const; // Check if the mob has reached the end.
  Direction getDirectionToNextPoint() const; // Get the direction to the next
                                             // point in the path.
private:
  Direction direction;
  AnimatedSprite sprite;
  sf::Vector2f position;
  sf::CircleShape shape;
  Path &path;
  int currentPathPoint;
  float speed;
  int maxHp;
  int hp;
  float size;
};
