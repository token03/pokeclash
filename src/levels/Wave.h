#pragma once

#include "../entities/MobFactory.hpp"
#include <vector>

struct MobBatch {
  PokemonType type;
  int quantity;
  float spawnInterval;

  MobBatch(PokemonType type, int quantity, float spawnInterval)
      : type(type), quantity(quantity), spawnInterval(spawnInterval) {}
};

class Wave {
public:
  Wave(std::initializer_list<MobBatch> batches);
  bool isFinished() const;
  void update(float dt);
  bool shouldSpawnMob() const { return spawnMob; }
  void mobSpawned() { spawnMob = false; }
  PokemonType getCurrentType() const;
  bool allMobsSpawned() const { return allSpawned; }

private:
  std::vector<MobBatch> batches;
  std::vector<MobBatch>::iterator currentBatch;
  float timer = 0;
  bool spawnMob = false;
  bool allSpawned;
};
;
