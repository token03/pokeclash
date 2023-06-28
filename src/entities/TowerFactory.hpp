#pragma once

#include "Mob.h"
#include "Tower.h"
#include <iostream>
#include <memory>
#include <vector>

class TowerFactory {
public:
  TowerFactory(const TowerFactory &) = default;
  TowerFactory(TowerFactory &&) = default;
  TowerFactory &operator=(const TowerFactory &) = default;
  TowerFactory &operator=(TowerFactory &&) = default;
  static std::unique_ptr<Tower> createTower(const std::string &pokemon,
                                            sf::Vector2f position) {
    try {
      return std::make_unique<Tower>(pokemon, position);
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      return nullptr;
    }
  }
};
