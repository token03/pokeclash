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
    std::string name;
    switch (type) {
    case PokemonType::Bulbasaur: {
      name = "Bulbasaur";
      break;
    }
    case PokemonType::Charmander: {
      name = "Charmander";
      break;
    }
    default:
      throw std::invalid_argument("Invalid mob type");
    }
    return std::make_unique<Mob>(path, name);
  }
};
