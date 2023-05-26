#include "Level.h"
#include <iostream>

Level::Level(int width, int height) : width(width), height(height), path() {
  towers.emplace_back(200, 200);
  std::cout << "Tower added" << std::endl;
  mobs.emplace_back(std::make_unique<Mob>(path));
  std::cout << "Mob added" << std::endl;
}
void Level::draw(sf::RenderWindow &window) {
  for (Tower &tower : towers) {
    tower.draw(window);
  }
  for (const auto &mob : mobs) {
    mob->draw(window);
  }
  path.draw(window);
}
void Level::update(float dt) {
  for (Tower &tower : towers) {
    // Clear the tower's targets before adding new ones.
    tower.clearTargets();
    for (const auto &mob : mobs) {
      // If the mob is in range of the tower, add it to the tower's targets.
      if (tower.isInRange(*mob)) {
        tower.addTarget(mob.get());
      }
      // Update the mob's position or state.
      if (mob->isDead()) {
        mobs.erase(mobs.begin());
      } else {
        mob->update(dt);
      }
    }
    // After adding all the targets, update the tower's state.
    tower.update(dt);
  }
}

void Level::addTower(int x, int y) { towers.emplace_back(x, y); }
