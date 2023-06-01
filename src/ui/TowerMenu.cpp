#include "TowerMenu.h"

TowerMenu::TowerMenu(Tower *tower) : tower_(tower) {}

void TowerMenu::render() {
  ImGui::Begin("Tower Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

  if (tower_) {
    ImGui::Text("Tower at (%f, %f)", tower_->getPosition().x,
                tower_->getPosition().y);

    if (ImGui::Button("Upgrade")) {
      tower_->upgrade();
    }
  }

  ImGui::End();
}
