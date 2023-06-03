#include "TowerMenu.h"

TowerMenu::TowerMenu(Tower *tower) : tower_(tower), visible(true) {}

void TowerMenu::render() {

  ImGui::Begin("Tower Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

  if (tower_) {
    ImGui::Text("Name: %s", tower_->getName().c_str());

    if (ImGui::Button("Upgrade")) {
      tower_->upgrade();
    }
  }

  ImGui::End();
}

void TowerMenu::toggle() { visible = !visible; }
