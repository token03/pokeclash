#include "Level.h"

Level::Level(int width, int height) : width(width), height(height) {}

void Level::draw(sf::RenderWindow &window) {
  for (Tower &tower : towers) {
    tower.draw(window);
  }

  for (Mob &mob : mobs) {
    mob.draw(window);
  }
}
