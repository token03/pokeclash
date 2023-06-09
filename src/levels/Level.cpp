#include "Level.h"
#include <iostream>
#include <math.h>

using std::cout, std::endl;

Level::Level(int width, int height) : width(width), height(height), path() {
  credits = 999;
  health = 100;
  setBackground();
  Wave testWave(
      {MobBatch("Bulbasaur", 3, 2.0f), MobBatch("Charmander", 3, 2.0f)});
  waves.push_back(std::move(testWave));
  std::cout << TypeChecker::getInstance().getMultiplier(Type::Fire, Type::Grass)
            << std::endl;
}

void Level::draw(sf::RenderWindow &window) {
  window.draw(backgroundSprite);
  path.draw(window);
  for (const auto &mob : mobs) {
    mob->draw(window);
  }
  for (const auto &mob : mobs) {
    mob->drawHpBar(window);
  }
  for (const auto &tower : towers) {
    tower->draw(window);
  }
  for (const auto &projectile : projectiles) {
    projectile->draw(window);
  }
}

void Level::update(float dt) {
  updateWave(dt);
  updateMobs(dt);
  updateTowers(dt);
  updateProjectiles(dt);
}

void Level::updateMobs(float dt) {
  for (auto mob = mobs.begin(); mob != mobs.end();) {
    if ((*mob)->isDead()) {
      credits += 10;         // increase credits
      mob = mobs.erase(mob); // remove dead mob
    } else if ((*mob)->hasReachedFinalPoint()) {
      health--;              // decrease health
      mob = mobs.erase(mob); // remove mob that reached the end
    } else {
      (*mob)->update(dt);
      ++mob;
    }
  }
}

void Level::updateTowers(float dt) {
  for (auto &tower : towers) {
    tower->clearTargets();
    for (auto &mob : mobs) {
      if (tower->isInRange(*mob)) {
        tower->addTarget(mob.get());
      }
    }
    tower->update(dt);

    // Attempt to shoot from tower, if successful, add projectile to Level's
    // list.
    auto projectile = tower->useMove();
    if (projectile) {
      projectiles.push_back(std::move(projectile));
    }
  }
}

void Level::updateWave(float dt) {
  if (!waves.empty()) {
    Wave &currentWave = waves.front();
    currentWave.update(dt);

    if (currentWave.allMobsSpawned() && mobs.empty()) {
      waves.erase(waves.begin());
    } else {
      if (currentWave.shouldSpawnMob()) {
        addMob(currentWave.getCurrentType());
        currentWave.mobSpawned();
      }
    }
  } else {
    Wave testWave(
        {MobBatch("Bulbasaur", 3, 1.0f), MobBatch("Charmander", 3, 1.0f)});
    waves.push_back(std::move(testWave));
  }
}

void Level::updateProjectiles(float dt) {
  for (size_t i = 0; i < projectiles.size(); ++i) {
    if (projectiles[i]->isCollidingWithTarget()) {
      projectiles[i]->onHit();
      projectiles.erase(projectiles.begin() + i);
      // Decrease the index to ensure we don't skip the next projectile.
      --i;
    } else if (projectiles[i]->isOutOfBounds(height, width)) {
      projectiles.erase(projectiles.begin() + i);
      // Decrease the index to ensure we don't skip the next projectile.
      --i;
    } else {
      projectiles[i]->update(dt);
    }
  }
}

void Level::addTower(const std::string &pokemon, sf::Vector2f position) {
  if (validTowerPlacement(position, 20)) {
    cout << "Tower added at " << position.x << ", " << position.y << endl;
    towers.push_back(TowerFactory::createTower(
        pokemon, sf::Vector2f((float)position.x, (float)position.y)));
  } else {
    cout << "Invalid tower placement" << endl;
  }
}

void Level::sellTower(Tower *tower) {
  for (auto it = towers.begin(); it != towers.end(); ++it) {
    if ((*it)->getPosition() == tower->getPosition()) {
      std::cout << "Tower at " << (*it)->getPosition().x << ", "
                << (*it)->getPosition().y << " sold\n";
      towers.erase(it);
      break;
    }
  }
}

void Level::addMob(const std::string &type) {
  mobs.push_back(MobFactory::createMob(type, path));
  cout << "Mob added" << endl;
}

bool Level::validTowerPlacement(sf::Vector2f position, int radius) {
  // Check if the position is within the bounds of the level.
  if (position.x - radius < 0 || position.x + radius >= width ||
      position.y - radius < 0 || position.y + radius >= height) {
    cout << "Out of bounds" << endl;
    return false;
  }

  // Check if the position overlaps with an existing tower.
  for (const auto &tower : towers) {
    sf::Vector2f towerPos = tower->getPosition();
    float distance =
        sqrt(pow(towerPos.x - position.x, 2) + pow(towerPos.y - position.y, 2));
    if (distance < radius + tower->getRadius()) { // change getRadius() with
                                                  // actual tower's radius
      cout << "Overlaps with an existing tower" << endl;
      return false;
    }
  }

  // Check if the position is on the path.
  return !path.overlap(position, radius);
}

Tower *Level::getTowerAtPosition(sf::Vector2f position) {
  for (const auto &tower : towers) {
    if (tower->isClicked(position)) {
      return tower.get();
    }
  }
  return nullptr;
}

void Level::setBackground() {
  if (!backgroundTexture.loadFromFile("../assets/bg/town.png")) {
    std::cerr << "Failed to load background image\n";
  }
  backgroundSprite.setTexture(backgroundTexture);
  sf::Vector2u textureSize = backgroundTexture.getSize();
  float scaleX = static_cast<float>((float)width / textureSize.x);
  float scaleY = static_cast<float>((float)height / textureSize.y);
  backgroundSprite.setScale(scaleX, scaleY);
}
