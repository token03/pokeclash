#pragma once

#include "../entities/MobFactory.hpp"
#include <vector>

using std::string;
struct MobBatch {
  string type;
  int quantity;
  float spawnInterval;

  MobBatch(string type, int quantity, float spawnInterval)
      : type(type), quantity(quantity), spawnInterval(spawnInterval) {}
};

class Wave {
public:
  Wave(std::initializer_list<MobBatch> batches);
  bool isFinished() const;
  void update(float dt);
  bool shouldSpawnMob() const { return spawnMob; }
  void mobSpawned() { spawnMob = false; }
  string getCurrentType() const;
  bool allMobsSpawned() const { return allSpawned; }

private:
  std::vector<MobBatch> batches;
  std::vector<MobBatch>::iterator currentBatch;
  float timer = 0;
  bool spawnMob = false;
  bool allSpawned;
};
;
