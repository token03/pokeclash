#include "Wave.h"

Wave::Wave(std::initializer_list<MobBatch> batches)
    : batches(batches), currentBatch(this->batches.begin()), timer(0.0f),
      spawnMob(false) {}

bool Wave::isFinished() const { return currentBatch == batches.end(); }

void Wave::update(float dt) {
  if (isFinished()) {
    return;
  }
  if (spawnMob == false) {
    timer += dt;
  }
  if (timer >= currentBatch->spawnInterval && currentBatch->quantity > 0) {
    timer = 0.0f;
    currentBatch->quantity--;
    spawnMob = true;
  }
  // We wait until the next update cycle after mob is spawned to increment
  // currentBatch
  if (spawnMob == false && currentBatch->quantity == 0) {
    ++currentBatch;
  }
}
PokemonType Wave::getCurrentType() const {
  if (isFinished()) {
    throw std::runtime_error("Wave is finished, no current type");
  }
  return currentBatch->type;
}
