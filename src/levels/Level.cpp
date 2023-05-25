#include "Level.h"
#include <iostream>

Level::Level(int width, int height) : width(width), height(height) {}

void Level::draw(sf::RenderWindow &window) {
  for (Tower &tower : towers) {
    tower.draw(window);
  }

  for (Mob &mob : mobs) {
    mob.draw(window);
  }
}
void Level::update(float dt) {
  for (Tower &tower : towers) {
    // Clear the tower's targets before adding new ones.
    tower.clearTargets();
    for (Mob &mob : mobs) {
      // If the mob is in range of the tower, add it to the tower's targets.
      if (tower.isInRange(mob)) {
        tower.addTarget(&mob);
      }

      // Update the mob's position or state.
      mob.update(dt);
    }

    // After adding all the targets, update the tower's state.
    tower.update(dt);
  }
}
