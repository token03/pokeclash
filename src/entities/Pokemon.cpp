#include "Pokemon.h"
#include <cstring>
#include <iostream>
#include <pugixml.hpp>

Pokemon::Pokemon(const std::string &name, sf::Vector2f pos)
    : position(pos), direction(Direction::South) {
  loadPokemonData(name);
}

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
      data.primaryType =
          TypeChecker::mapStringToType(pokemonNode.child_value("PrimaryType"));
      data.secondaryType = TypeChecker::mapStringToType(
          pokemonNode.child_value("SecondaryType"));
      data.walkingAnimation = pokemonNode.child_value("WalkingAnimation");
      data.shootingAnimation = pokemonNode.child_value("ShootingAnimation");
      data.attackAnimation = pokemonNode.child_value("AttackAnimation");
      data.idleAnimation = pokemonNode.child_value("IdleAnimation");
      data.towerBaseDamage = std::stoi(pokemonNode.child_value("TowerDamage"));
      data.towerAttacksPerSecond =
          std::stoi(pokemonNode.child_value("TowerAttackSpeed"));
      data.towerBaseRange = std::stoi(pokemonNode.child_value("TowerRange"));
      data.mobHP = std::stoi(pokemonNode.child_value("MobHP"));
      data.mobSpeed = std::stoi(pokemonNode.child_value("MobSpeed"));
      data.hitboxRadius = std::stoi(pokemonNode.child_value("HitboxRadius"));
      data.preEvolutionName = pokemonNode.child_value("PreEvolution");
      data.evolutionName = pokemonNode.child_value("Evolution");
      if (std::strcmp(pokemonNode.child_value("EvolutionLevel"), "") != 0)
        data.evolutionLevel =
            std::stoi(pokemonNode.child_value("EvolutionLevel"));
      return data;
    }
  }

  throw std::runtime_error("Pokemon not found: " + name);
}
