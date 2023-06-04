#pragma once

#include "../graphics/TextureManager.h"
#include "Mob.h"
#include <memory>
#include <vector>

enum class MobType {
  Charmander,
};

class TowerFactory {
public:
  static std::unique_ptr<Mob> createMob(const MobType type, int x, int y,
                                        TextureManager &textureManager) {
    if (type == MobType::Charmander) {
      return std::make_unique<CharmanderTower>(x, y, textureManager);
    } else {
      throw std::invalid_argument("Invalid mob type");
    }
  }
};
