#include "TowerMenu.h"

TowerMenu::TowerMenu(Tower *tower, Level *level)
    : tower_(tower), visible(true), level_(level) {}

void TowerMenu::render() {

  ImGui::Begin("Tower Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

  if (tower_) {
    ImGui::Text("Name: %s", tower_->getName().c_str());
    ImGui::Text("Level: %d", tower_->getLevel());
    ImGui::Text("Damage: %.2f", tower_->getDamage());
    ImGui::Text("Range: %.2f", tower_->getRange());
    ImGui::Text("Position: (%f, %f)", tower_->getPosition().x,
                tower_->getPosition().y);

    if (ImGui::Button("Upgrade")) {
      tower_->upgrade(99);
    }

    if (ImGui::Button("Sell")) {
      level_->sellTower(tower_);
      tower_ = nullptr;
      visible = false;
    }
  }
  ImGui::End();
}

void TowerMenu::setTower(Tower *tower) { tower_ = tower; }

void TowerMenu::toggle() { visible = !visible; }
