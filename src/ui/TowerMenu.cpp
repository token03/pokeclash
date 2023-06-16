#include "TowerMenu.h"

TowerMenu::TowerMenu(Tower *tower, Level *level)
    : tower_(tower), visible(true), level_(level) {}

void TowerMenu::render() {
  ImGui::Begin("Tower Menu", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::SetWindowFontScale(1.5f); // Increase the size of the text in the UI

  if (tower_) {
    ImGui::Text("Name: %s", tower_->getName().c_str());
    ImGui::Text("Level: %d", tower_->getLevel());
    ImGui::Text("Damage: %.2f", tower_->getDamage());
    ImGui::Text("Range: %.2f", tower_->getRange());
    ImGui::Text("Position: (%f, %f)", tower_->getPosition().x,
                tower_->getPosition().y);

    // Set the button size
    ImVec2 buttonSize(ImGui::GetContentRegionAvail().x / 2 - 10,
                      0); // Divide width evenly for two buttons

    // Position the buttons side by side
    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, buttonSize.x);
    ImGui::SetColumnWidth(1, buttonSize.x);

    // Button 1: Upgrade
    if (ImGui::Button("Upgrade", buttonSize)) {
      tower_->upgrade(99);
    }
    ImGui::NextColumn();

    // Button 2: Sell
    if (ImGui::Button("Sell", buttonSize)) {
      level_->sellTower(tower_);
      tower_ = nullptr;
      visible = false;
    }

    ImGui::Columns(1); // Reset columns
  }
  ImGui::End();
}

void TowerMenu::setTower(Tower *tower) { tower_ = tower; }

void TowerMenu::toggle() { visible = !visible; }
