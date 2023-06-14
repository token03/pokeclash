#include "CharmanderLine.h"
#include <iostream>

CharmanderTower::CharmanderTower(int posX, int posY) : Tower(posX, posY) {
  // Here you can set attributes that are specific to a Charmander tower.
  // For example, you might set the tower's range and damage based on what you
  // want for a Charmander tower.
  name = "Charmander";
  setSprite(name);
  range = 100;
  damage = 10;
  animations[TowerState::Idle] = AnimatedSprite("KyogreIdle");
  animations[TowerState::Attacking] = AnimatedSprite("KyogreAttack");
}

int CharmanderTower::upgrade(int money) {
  if (money < upgradeCost || level == 100)
    return 0;

  level++;
  damage += 5;

  if (stage == TowerStage::First && level >= 15) {
    stage = TowerStage::Second;
    name = "Charmeleon";
    setSprite("Bulbasaur");
    range = 200;
    damage = 20;
  } else if (stage == TowerStage::Second && level >= 30) {
    stage = TowerStage::Third;
    name = "Charizard";
    range = 300;
    damage = 30;
  }

  return upgradeCost;
}
