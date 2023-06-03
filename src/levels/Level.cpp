#include "Level.h"

Level::Level(int width, int height, TextureManager &textureManager)
    : width(width), height(height), path(), textureManager(textureManager) {
  addTower(TowerType::Charmander, 200, 200);
  mobs.emplace_back(std::make_unique<Mob>(path));
  std::cout << "Mob added" << std::endl;
  credits = 999;
  health = 100;
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
  mobTimer += dt;
  if (mobTimer >= 1.0f) {
    mobs.emplace_back(std::make_unique<Mob>(path));
    mobTimer = 0.0f;
  }

  for (auto &mob : mobs) {
    if (mob->isDead()) {
      credits += 10;            // increase credits
      mobs.erase(mobs.begin()); // remove dead mob
      break;
    }
    if (mob->hasReachedFinalPoint()) {
      health--;                 // decrease health
      mobs.erase(mobs.begin()); // remove mob that reached the end
      break;
    }
    mob->update(dt);
  }
  for (auto &tower : towers) {
    tower->clearTargets();
    for (auto &mob : mobs) {
      if (tower->isInRange(*mob)) {
        tower->addTarget(mob.get());
      }
    }
    tower->update(dt);
  }
}

void Level::addTower(const TowerType type, int x, int y) {
  if (validTowerPlacement(sf::Vector2i(x, y), 10)) {
    std::cout << "Tower added" << std::endl;
    towers.push_back(TowerFactory::createTower(type, x, y, textureManager));
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
