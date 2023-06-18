#include "Pokemon.h"
#include <pugixml.hpp>

Pokemon::Pokemon(sf::Vector2f pos)
    : position(pos), direction(Direction::South) {}

void Pokemon::setPosition(const sf::Vector2f &pos) { position = pos; }

PokemonData Pokemon::loadPokemonData(const std::string &name) {
  pugi::xml_document doc;
  if (!doc.load_file("../src/data/Pokemon.xml")) {
    throw std::runtime_error("Failed to load Pokemon.xml");
  }

  pugi::xml_node pokemonsNode = doc.child("Pokemons");

  for (pugi::xml_node pokemonNode = pokemonsNode.child("Pokemon"); pokemonNode;
       pokemonNode = pokemonNode.next_sibling("Pokemon")) {
    if (pokemonNode.child_value("Name") == name) {
      PokemonData data;
      data.name = name;
      data.type1 = pokemonNode.child_value("Type1");
      data.type2 = pokemonNode.child_value("Type2");
      data.walkingAnimation = pokemonNode.child_value("WalkingAnimation");
      data.shootingAnimation = pokemonNode.child_value("ShootingAnimation");
      data.attackAnimation = pokemonNode.child_value("AttackAnimation");
      data.idleAnimation = pokemonNode.child_value("IdleAnimation");
      data.towerAttack = std::stoi(pokemonNode.child_value("TowerAttack"));
      data.towerSpeed = std::stoi(pokemonNode.child_value("TowerSpeed"));
      data.towerRange = std::stoi(pokemonNode.child_value("TowerRange"));
      data.mobHP = std::stoi(pokemonNode.child_value("MobHP"));
      data.mobSpeed = std::stoi(pokemonNode.child_value("MobSpeed"));
      data.mobHitbox = std::stoi(pokemonNode.child_value("MobHitbox"));
      data.preEvolution = pokemonNode.child_value("PreEvolution");
      data.evolution = pokemonNode.child_value("Evolution");

      return data;
    }
  }

  throw std::runtime_error("Pokemon not found: " + name);
}
