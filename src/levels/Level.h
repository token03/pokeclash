#ifndef LEVEL_H
#define LEVEL_H

#include "../entities/Mob.h"
#include "../entities/Tower.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
  Level(int width, int height);
  void draw(sf::RenderWindow &window);
  std::vector<Tower> &getTowers() { return towers; }
  std::vector<Mob> &getMobs() { return mobs; }

private:
  std::vector<Tower> towers;
  std::vector<Mob> mobs;
  int width;
  int height;
};

#endif
