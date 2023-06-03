#include "CharmanderLine.h"

CharmanderTower::CharmanderTower(int posX, int posY,
                                 TextureManager &textureManager)
    : Tower(posX, posY, textureManager) {
  // Here you can set attributes that are specific to a Charmander tower.
  // For example, you might set the tower's range and damage based on what you
  // want for a Charmander tower.
  name = "Charmander";
  setSprite(name);
  range = 100;
  damage = 10;
}

void CharmanderTower::upgrade() {
  if (stage == TowerStage::FIRST) {
    stage = TowerStage::SECOND;
    name = "Charmeleon";
    setSprite("Bulbasaur");
    range = 200;
    damage = 20;
  } else if (stage == TowerStage::SECOND) {
    stage = TowerStage::THIRD;
    name = "Charizard";
    range = 300;
    damage = 30;
  }
}
