#pragma once

#include "../graphics/TextureManager.h"
#include "Mob.h"
#include "TowerFactory.hpp"
#include <memory>
#include <vector>

class MobFactory {
public:
  static std::unique_ptr<Mob> createMob(const PokemonType type, Path &path) {
    TextureManager &textureManager = TextureManager::getInstance();
    sf::Texture &texture =
        textureManager.getRef("Charmander"); // filler default value
    switch (type) {
    case PokemonType::Bulbasaur:
      texture = textureManager.getRef("Bulbasaur");
      return std::make_unique<Mob>(path, 100, 50, 10, texture);
      break;
    case PokemonType::Charmander:
      texture = textureManager.getRef("Charmander");
      return std::make_unique<Mob>(path, 100, 50, 10, texture);
      break;
    default:
      throw std::invalid_argument("Invalid mob type");
      break;
    }
  }
};
