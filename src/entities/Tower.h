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
enum class TowerState { Idle, Attacking };

class Tower : public Pokemon {
public:
  Tower(sf::Vector2f position);                // Constructor.
  void draw(sf::RenderWindow &window);         // Draw the tower.
  bool isInRange(const Mob &mob) const;        // Check if the mob is in range.
  bool isClicked(sf::Vector2i clickPos) const; // Check if the tower is clicked.
  void clearTargets();                         // Clear the tower's targets.
  void addTarget(Mob *mob);           // Add a mob to the tower's targets.
  virtual int upgrade(int money) = 0; // Upgrade the tower.
  void sell();                        // Sell the tower.
  virtual void update(float dt);      // Update the tower's state.
  sf::Vector2f getPosition() const { return position; } // Returns position.
  std::string getName() const { return name; }  // Returns the tower's name.
  float getDamage() const { return damage; }    // Returns the tower's damage.
  float getRange() const { return range; }      // Returns the tower's range.
  float getRadius() const { return radius; }    // Returns the tower's radius.
  int getCost() const { return cost; }          // Returns the tower's cost.
  int getLevel() const { return level; }        // Returns the tower's level.
  TowerStage getStage() const { return stage; } // Returns the tower's stage.
  void setSprite(std::string);                  // Sets the tower's sprite.
  Direction getDirectionToTarget(const Mob *target) const;
  bool hasBeenSold() const { return isSold; } // Returns if the tower is sold.

protected:
  TowerStage stage;
  TowerState state;
  std::map<TowerState, std::unique_ptr<AnimatedSprite>> animations;
  std::string name;
  std::vector<Mob *> targets;
  std::vector<Projectile> projectiles;
  float attackTimer;
  float attackDelay;
  float range;
  float damage;
  float radius;
  int level;
  int windowHeight;
  int windowWidth;
  int cost;
  int upgradeCost;
  int maxTargets;
  bool isSold;
};
