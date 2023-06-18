#pragma once
#include "../graphics/AnimatedSprite.h"
#include "Type.hpp"

/* enum class PokemonType { Pikachu, Charmander, Squirtle, Bulbasaur }; */

struct PokemonData {
  std::string name;
  std::string type1;
  std::string type2; // This is optional and may be empty
  std::string walkingAnimation;
  std::string shootingAnimation;
  std::string attackAnimation;
  std::string idleAnimation;
  int towerAttack;
  int towerSpeed;
  int towerRange;
  int mobHP;
  int mobSpeed;
  int mobHitbox;
  std::string preEvolution; // This is optional and may be empty
  std::string evolution;    // This is optional and may be empty
};

class Pokemon {
public:
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
