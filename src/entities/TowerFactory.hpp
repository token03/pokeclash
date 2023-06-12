#pragma once

#include "Mob.h"
#include "Tower.h"
#include "towers/CharmanderLine.h" // Include all types of towers
#include <memory>
#include <vector>

enum class PokemonType {
  Charmander,
  Bulbasaur,
  Squirtle,
};

class TowerFactory {
public:
  static std::unique_ptr<Tower> createTower(const PokemonType type, int x,
                                            int y) {
    if (type == PokemonType::Charmander) {
      return std::make_unique<CharmanderTower>(x, y);
    } else {
      throw std::invalid_argument("Invalid tower type");
    }
  }
};
