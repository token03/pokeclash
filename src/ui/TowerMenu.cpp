#include "TowerMenu.h"

TowerMenu::TowerMenu(Tower *tower) : tower_(tower), visible(true) {}

void TowerMenu::render() {

  ImGui::Begin("Tower Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

  if (tower_) {
    ImGui::Text("Name: %s", tower_->getName().c_str());
    ImGui::Text("Level: %d", tower_->getLevel());
    ImGui::Text("Damage: %.2f", tower_->getDamage());
    ImGui::Text("Range: %.2f", tower_->getRange());

    if (ImGui::Button("Upgrade")) {
      tower_->upgrade(99);
    }
  }

  ImGui::End();
}

void TowerMenu::toggle() { visible = !visible; }
