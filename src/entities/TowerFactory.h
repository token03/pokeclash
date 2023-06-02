#pragma once

#include "Mob.h"
#include "Tower.h"
#include "towers/CharmanderLine.h" // Include all types of towers
#include <memory>
#include <vector>

enum class TowerType {
  Charmander,
  // Add other types of towers here
  // OtherTower,
};

class TowerFactory {
public:
  static std::unique_ptr<Tower> createTower(const TowerType type, int x,
                                            int y) {
    if (type == TowerType::Charmander) {
      return std::make_unique<CharmanderTower>(x, y);
    }
    // add other types of towers here
    // else if(type == "OtherTower") {
    //   return std::make_unique<OtherTower>(x, y);
    // }
    else {
      throw std::invalid_argument("Invalid tower type");
    }
  }
};
