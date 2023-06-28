#pragma once

#include "../graphics/AnimatedSprite.h"
#include "../graphics/TextureManager.h"
#include "../levels/Path.h"
#include "Pokemon.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Mob : public Pokemon {
public:
  Mob(Path &path, const std::string &name);
  void draw(sf::RenderWindow &window) override; // Draw the mob.
  void setPokemon(PokemonData &data) override;  // Set the mob's stats.
  void drawHpBar(sf::RenderWindow &window);     // Draw the mob's HP bar.
  sf::Vector2f getPosition() const { return position; } // Get position.
  void update(float dt) override;              // Update the mob's state.
  bool isDead() const { return hp <= 0; }      // Check if the mob is dead.
  void onHit(int damage);                      // Called when the mob is hit.
  int getSize() const { return hitboxRadius; } // Get the mob's size.
  int getCost() const;                         // Get the mob's cost.
  bool hasReachedFinalPoint() const; // Check if the mob has reached the end.
  Direction getDirectionToNextPoint() const; // Get the direction to the next
                                             // point in the path.
private:
  Path &path;
  int currentPathPoint;
  int cost;
  float speed;
  int maxHp;
  int hp;
  float hitboxRadius;
};
