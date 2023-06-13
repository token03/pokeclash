#pragma once

#include "../graphics/TextureManager.h"
#include "Mob.h"
#include "TowerFactory.hpp"
#include <memory>

class MobFactory {
public:
  MobFactory(const MobFactory &) = default;
  MobFactory(MobFactory &&) = default;
  MobFactory &operator=(const MobFactory &) = default;
  MobFactory &operator=(MobFactory &&) = default;
  static std::unique_ptr<Mob> createMob(const PokemonType type, Path &path) {
    TextureManager &textureManager = TextureManager::getInstance();
    switch (type) {
    case PokemonType::Bulbasaur: {
      sf::Texture &texture = textureManager.getRef("Bulbasaur");
      return std::make_unique<Mob>(path, 100, 50, 10, texture);
    }
    case PokemonType::Charmander: {
      sf::Texture &texture = textureManager.getRef("Charmander");
      return std::make_unique<Mob>(path, 100, 50, 10, texture);
    }
    default:
      throw std::invalid_argument("Invalid mob type");
    }
  }
};
