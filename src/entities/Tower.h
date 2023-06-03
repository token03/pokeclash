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
  Tower(int posX, int posY, TextureManager &textureManager); // Constructor.
  void draw(sf::RenderWindow &window);                       // Draw the tower.
  bool isInRange(const Mob &mob) const; // Check if the mob is in range.
  bool isClicked(int x, int y) const;   // Check if the tower is clicked.
  void clearTargets();                  // Clear the tower's targets.
  void addTarget(Mob *mob);             // Add a mob to the tower's targets.
  virtual void upgrade() = 0;           // Upgrade the tower.
  void sell();                          // Sell the tower.
  void update(float dt);                // Update the tower's state.
  sf::Vector2f getPosition();           // Returns the tower's position.
  std::string getName();                // Returns the tower's name.
  float getDamage();                    // Returns the tower's damage.
  float getRange();                     // Returns the tower's range.
  float getRadius();                    // Returns the tower's radius.
  int getCost();                        // Returns the tower's cost.
  int getSellValue();                   // Returns the tower's sell value.
  TowerStage getStage();                // Returns the tower's stage.
  std::vector<Mob *> getTargets();      // Returns the tower's targets.
  void setSprite(std::string);          // Sets the tower's sprite.

protected:
  TextureManager &textureManager;
  TowerStage stage = TowerStage::FIRST;
  std::string name;
  std::vector<Mob *> targets;
  std::vector<Projectile> projectiles;
  sf::CircleShape shape;
  sf::Vector2f position;
  sf::Sprite sprite;
  float attackTimer = 0.0f, attackDelay = 0.25f;
  float range;
  float damage;
  float radius;
  int windowHeight;
  int windowWidth;
};
