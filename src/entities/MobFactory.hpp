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
  static std::unique_ptr<Mob> createMob(const std::string &pokemon,
                                        Path &path) {
    try {
      return std::make_unique<Mob>(path, pokemon);
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      return nullptr;
    }
  }
};
