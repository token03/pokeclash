#pragma once
#include "../graphics/AnimatedSprite.h"
#include "Type.hpp"

struct PokemonData {
  std::string name;
  Type primaryType;
  Type secondaryType; // This is optional and may be empty
  std::string walkingAnimation;
  std::string shootingAnimation;
  std::string attackAnimation;
  std::string idleAnimation;
  int towerBaseDamage;
  float towerAttacksPerSecond;
  float towerBaseRange;
  int towerCost;
  int mobHP;
  int mobSpeed;
  int hitboxRadius;
  std::string preEvolutionName;
  std::string evolutionName;
  int evolutionLevel;
};

enum class State { Idle, Attacking, Walking, Dead };

class Pokemon {
public:
  Pokemon(const std::string &name, sf::Vector2f pos);
  Pokemon(sf::Vector2f pos);
  sf::Vector2f getPosition() const { return position; }
  Direction getDirection() const { return direction; }
  void setPosition(const sf::Vector2f &pos);
  void setDirection(Direction dir) { direction = dir; }
  void draw(sf::RenderWindow &window);
  void update(float dt);
  static PokemonData loadPokemonData(const std::string &name);

protected:
  sf::Vector2f position;
  Direction direction;
};
