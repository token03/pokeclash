#pragma once

#include "../graphics/AnimatedSprite.h"
#include "../graphics/TextureManager.h"
#include "Mob.h"
#include "Pokemon.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

enum class TowerStage { First, Second, Third };

class Tower : public Pokemon {
public:
  Tower(sf::Vector2f position);                          // Constructor.
  Tower(const std::string &name, sf::Vector2f position); // Constructor.
  void draw(sf::RenderWindow &window) override;          // Draw the tower.
  void setPokemon(PokemonData data) override;  // Set the tower's stats.
  bool isInRange(const Mob &mob) const;        // Check if the mob is in range.
  bool isClicked(sf::Vector2f clickPos) const; // Check if the tower is clicked.
  void clearTargets();                         // Clear the tower's targets.
  void addTarget(Mob *mob);       // Add a mob to the tower's targets.
  int upgrade(int money);         // Upgrade the tower.
  void sell();                    // Sell the tower.
  void update(float dt) override; // Update the tower's state.
  sf::Vector2f getPosition() const { return position; } // Returns position.
  std::string getName() const { return name; } // Returns the tower's name.
  float getDamage() const { return damage; }   // Returns the tower's damage.
  float getRange() const { return range; }     // Returns the tower's range.
  float getRadius() const { return hitboxRadius; } // Returns radius.
  int getCost() const { return cost; }             // Returns the tower's cost.
  int getLevel() const { return level; }           // Returns the tower's level.
  TowerStage getStage() const { return stage; }    // Returns the tower's stage.
  void setSprite(std::string);                     // Sets the tower's sprite.
  Direction getDirectionToTarget(const Mob *target) const;

protected:
  TowerStage stage;
  std::vector<Mob *> targets;
  std::vector<Projectile> projectiles;
  std::string name;
  float attackTimer;
  float attackDelay;
  float baseRange;
  float range;
  int baseDamage;
  int damage;
  float hitboxRadius;
  int level;
  int windowHeight;
  int windowWidth;
  int cost;
  int upgradeCost;
  int maxTargets;
};
