#include "CharmanderLine.h"

CharmanderTower::CharmanderTower(int posX, int posY) : Tower(posX, posY) {
  // Here you can set attributes that are specific to a Charmander tower.
  // For example, you might set the tower's range and damage based on what you
  // want for a Charmander tower.
}

void CharmanderTower::upgrade() {
  if (stage == TowerStage::FIRST) {
    stage = TowerStage::SECOND;
    range = 200; // These are just examples. Adjust based on your game design.
    damage = 20;
  } else if (stage == TowerStage::SECOND) {
    stage = TowerStage::THIRD;
    range = 300;
    damage = 30;
  }
}
