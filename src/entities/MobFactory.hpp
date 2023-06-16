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
    std::string aniKey;
    int maxHp;
    float speed;
    int size;
    switch (type) {
    case PokemonType::Bulbasaur: {
      maxHp = 100;
      speed = 40;
      size = 20;
      aniKey = "BulbasaurWalk";
      break;
    }
    case PokemonType::Charmander: {
      maxHp = 100;
      speed = 30;
      size = 20;
      aniKey = "CharmanderWalk";
      break;
    }
    default:
      throw std::invalid_argument("Invalid mob type");
    }
    return std::make_unique<Mob>(path, maxHp, speed, size, aniKey);
  }
};
