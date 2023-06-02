#include "Level.h"

Level::Level(int width, int height) : width(width), height(height), path() {
  addTower(TowerType::Charmander, 200, 200);
  std::cout << "Tower added" << std::endl;
  mobs.emplace_back(std::make_unique<Mob>(path));
  std::cout << "Mob added" << std::endl;
}

void Level::draw(sf::RenderWindow &window) {
  for (const auto &tower : towers) {
    tower->draw(window);
  }
  for (const auto &mob : mobs) {
    mob->draw(window);
  }
  path.draw(window);
}

void Level::update(float dt) {
  for (const auto &tower : towers) {
    // Clear the tower's targets before adding new ones.
    tower->clearTargets();
    for (const auto &mob : mobs) {
      // If the mob is in range of the tower, add it to the tower's targets.
      if (tower->isInRange(*mob)) {
        tower->addTarget(mob.get());
      }
      // Update the mob's position or state.
      if (mob->isDead()) {
        mobs.erase(mobs.begin());
      } else {
        mob->update(dt);
      }
    }
    // After adding all the targets, update the tower's state.
    tower->update(dt);
  }
}

void Level::addTower(const TowerType type, int x, int y) {
  if (validTowerPlacement(sf::Vector2i(x, y), 10)) {
    std::cout << "Tower added" << std::endl;
    towers.push_back(TowerFactory::createTower(type, x, y));
  } else {
    std::cout << "Invalid tower placement" << std::endl;
  }
}

bool Level::validTowerPlacement(sf::Vector2i position, int radius) {
  // Check if the position is within the bounds of the level.
  if (position.x - radius < 0 || position.x + radius >= width ||
      position.y - radius < 0 || position.y + radius >= height) {
    std::cout << "Out of bounds" << std::endl;
    return false;
  }
  // Check if the position is on the path.
  return !path.overlap(position, radius);
}

Tower *Level::getTowerAtPosition(int x, int y) {
  for (const auto &tower : towers) {
    if (tower->isClicked(x, y)) {
      return tower.get();
    }
  }
  return nullptr;
}
