#include "CharmanderLine.h"
#include <iostream>

CharmanderTower::CharmanderTower(int posX, int posY) : Tower(posX, posY) {
  // Here you can set attributes that are specific to a Charmander tower.
  // For example, you might set the tower's range and damage based on what you
  // want for a Charmander tower.
  name = "Charmander";
  setSprite(name);
  range = 100;
  radius = 30;
  damage = 10;
  upgradeCost = 50;
  animations[TowerState::Idle] = AnimatedSprite("CharmanderIdle");
  animations[TowerState::Attacking] = AnimatedSprite("CharmanderAttack");
}

int CharmanderTower::upgrade(int money) {
  if (money < upgradeCost || level == 100)
    return 0;

  level++;
  damage += 5;

  if (stage == TowerStage::First && level >= 2) {
    stage = TowerStage::Second;
    name = "Charmeleon";
    animations[TowerState::Idle] = AnimatedSprite("CharmeleonIdle");
    animations[TowerState::Attacking] = AnimatedSprite("CharmeleonAttack");
    range = 200;
    damage = 20;
  } else if (stage == TowerStage::Second && level >= 3) {
    stage = TowerStage::Third;
    name = "Charizard";
    animations[TowerState::Idle] = AnimatedSprite("CharizardIdle");
    animations[TowerState::Attacking] = AnimatedSprite("CharizardAttack");
    range = 300;
    damage = 30;
  }

  return upgradeCost;
}
