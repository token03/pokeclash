#pragma once

#include "../graphics/TextureManager.h"
#include "Mob.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

enum class TowerStage { FIRST, SECOND, THIRD };

class Tower {
public:
  Tower(int posX, int posY);            // Constructor.
  void draw(sf::RenderWindow &window);  // Draw the tower.
  bool isInRange(const Mob &mob) const; // Check if the mob is in range.
  bool isClicked(int x, int y) const;   // Check if the tower is clicked.
  void clearTargets();                  // Clear the tower's targets.
  void addTarget(Mob *mob);             // Add a mob to the tower's targets.
  virtual int upgrade(int money) = 0;   // Upgrade the tower.
  void sell();                          // Sell the tower.
  void update(float dt);                // Update the tower's state.
  sf::Vector2f getPosition() const { return position; } // Returns position.
  std::string getName() const { return name; }  // Returns the tower's name.
  float getDamage() const { return damage; }    // Returns the tower's damage.
  float getRange() const { return range; }      // Returns the tower's range.
  float getRadius() const { return radius; }    // Returns the tower's radius.
  int getCost() const { return cost; }          // Returns the tower's cost.
  int getLevel() const { return level; }        // Returns the tower's level.
  TowerStage getStage() const { return stage; } // Returns the tower's stage.
  void setSprite(std::string);                  // Sets the tower's sprite.

protected:
  TextureManager &textureManager;
  TowerStage stage;
  std::string name;
  std::vector<Mob *> targets;
  std::vector<Projectile> projectiles;
  sf::Vector2f position;
  sf::Sprite sprite;
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
};
