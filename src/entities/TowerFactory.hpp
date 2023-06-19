#pragma once

#include "Mob.h"
#include "Tower.h"
#include <memory>
#include <vector>

enum class PokemonType {
  Charmander,
  Bulbasaur,
  Squirtle,
  Chimchar,
};

class TowerFactory {
public:
  TowerFactory(const TowerFactory &) = default;
  TowerFactory(TowerFactory &&) = default;
  TowerFactory &operator=(const TowerFactory &) = default;
  TowerFactory &operator=(TowerFactory &&) = default;
  static std::unique_ptr<Tower> createTower(const PokemonType type,
                                            sf::Vector2f position) {
    if (type == PokemonType::Charmander) {
      return std::make_unique<Tower>("Charmander", position);
    } else if (type == PokemonType::Chimchar) {
      return std::make_unique<Tower>("Chimchar", position);
    } else {
      throw std::invalid_argument("Invalid tower type");
    }
  }
};
