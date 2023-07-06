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
    if (pokemonNode.attribute("Name").value() == name) {
      PokemonData data;
      data.name = name;
      data.primaryType = TypeChecker::mapStringToType(
          pokemonNode.attribute("PrimaryType").value());
      data.secondaryType = TypeChecker::mapStringToType(
          pokemonNode.attribute("SecondaryType").value());

      pugi::xml_node animationsNode = pokemonNode.child("Animations");
      data.walkingAnimation = animationsNode.attribute("Walking").value();
      data.shootingAnimation = animationsNode.attribute("Shooting").value();
      data.attackAnimation = animationsNode.attribute("Attack").value();
      data.idleAnimation = animationsNode.attribute("Idle").value();

      pugi::xml_node towerNode = pokemonNode.child("Tower");
      data.towerBaseDamage = std::stoi(towerNode.attribute("Damage").value());
      data.towerAttacksPerSecond =
          std::stoi(towerNode.attribute("AttackSpeed").value());
      data.towerBaseRange = std::stoi(towerNode.attribute("Range").value());

      data.mobHP = std::stoi(pokemonNode.child("Mob").attribute("HP").value());
      data.mobSpeed =
          std::stoi(pokemonNode.child("Mob").attribute("Speed").value());

      data.hitboxRadius =
          std::stoi(pokemonNode.child("Hitbox").attribute("Radius").value());

      data.preEvolutionName =
          pokemonNode.child("PreEvolution").attribute("Name").value();
      data.evolutionName =
          pokemonNode.child("Evolution").attribute("Name").value();
      if (std::strcmp(pokemonNode.child("Evolution").attribute("Level").value(),
                      "") != 0)
        data.evolutionLevel = std::stoi(
            pokemonNode.child("Evolution").attribute("Level").value());
      return data;
    }
  }
  throw std::runtime_error("Pokemon not found: " + name);
}
