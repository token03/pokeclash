#include "Level.h"
#include <iostream>

using std::cout, std::endl;

Level::Level(int width, int height) : width(width), height(height), path() {
  credits = 999;
  health = 100;
  setBackground();
  Wave testWave({MobBatch(PokemonType::Bulbasaur, 3, 2.0f),
                 MobBatch(PokemonType::Charmander, 3, 2.0f)});
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
}

void Level::update(float dt) {
  updateWave(dt);
  updateMobs(dt);
  updateTowers(dt);
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
  }
}

void Level::updateWave(float dt) {
  if (!waves.empty()) {
    Wave &currentWave = waves.front();
    currentWave.update(dt);

    if (currentWave.isFinished()) {
      waves.erase(waves.begin());
    } else {
      if (currentWave.shouldSpawnMob()) {
        addMob(currentWave.getCurrentType());
        currentWave.mobSpawned();
      }
    }
  } else {
    Wave testWave({MobBatch(PokemonType::Bulbasaur, 3, 1.0f),
                   MobBatch(PokemonType::Charmander, 3, 1.0f)});
    waves.push_back(std::move(testWave));
  }
}

void Level::addTower(const PokemonType type, sf::Vector2f position) {
  if (validTowerPlacement(position, 20)) {
    cout << "Tower added at " << position.x << ", " << position.y << endl;
    towers.push_back(TowerFactory::createTower(
        type, sf::Vector2f((float)position.x, (float)position.y)));
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

void Level::addMob(const PokemonType type) {
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
