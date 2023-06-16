#include "CharmanderLine.h"
#include <iostream>

CharmanderTower::CharmanderTower(int posX, int posY) : Tower(posX, posY) {
  name = "Charmander";
  range = 100;
  radius = 15;
  damage = 10;
  upgradeCost = 50;
  animations[TowerState::Idle] =
      std::make_unique<AnimatedSprite>("CharmanderSleep");
  animations[TowerState::Attacking] =
      std::make_unique<AnimatedSprite>("CharmanderStrike");
}

int CharmanderTower::upgrade(int money) {
  if (money < upgradeCost || level == 100)
    return 0;

  level++;
  damage += 5;

  if (stage == TowerStage::First && level >= 2) {
    stage = TowerStage::Second;
    name = "Charmeleon";
    animations[TowerState::Idle] =
        std::make_unique<AnimatedSprite>("CharmeleonSleep");
    animations[TowerState::Attacking] =
        std::make_unique<AnimatedSprite>("CharmeleonShoot");
    range = 200;
    damage = 20;
  } else if (stage == TowerStage::Second && level >= 3) {
    stage = TowerStage::Third;
    name = "Charizard";
    animations[TowerState::Idle] =
        std::make_unique<AnimatedSprite>("ChariardSleep");
    animations[TowerState::Attacking] =
        std::make_unique<AnimatedSprite>("ChariardShoot");
    range = 300;
    damage = 30;
  }

  return upgradeCost;
}
