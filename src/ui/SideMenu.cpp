#include "SideMenu.h"

SideMenu::SideMenu(sf::RenderWindow &window, std::unique_ptr<Level> &level)
    : window(window), level(level) {}

void SideMenu::render() {
  ImGui::SetNextWindowPos(ImVec2(window.getSize().x * 0.85f, 0),
                          ImGuiCond_Always);
  ImGui::SetNextWindowSize(
      ImVec2(window.getSize().x * 0.15f, window.getSize().y), ImGuiCond_Always);

  ImGui::Begin("Side Menu", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  renderTowerPlacement();
  renderTowerManagement();
  renderStats();

  ImGui::End();
}

void SideMenu::renderTowerPlacement() {
  // Code for the tower placement section goes here

  if (ImGui::Button("Place Charmander")) {
    currentPokemonToPlace = PokemonType::Charmander;
  }

  // Add more Pokemon options here
}

void SideMenu::renderTowerManagement() {
  if (selectedTower) {
    if (ImGui::TreeNode("Tower Management")) {
      // Display tower information and controls
      ImGui::Text("Name: %s", selectedTower->getName().c_str());
      ImGui::Text("Level: %d", selectedTower->getLevel());
      ImGui::Text("Damage: %.2f", selectedTower->getDamage());
      ImGui::Text("Range: %.2f", selectedTower->getRange());
      ImGui::Text("Position: (%f, %f)", selectedTower->getPosition().x,
                  selectedTower->getPosition().y);

      if (ImGui::Button("Upgrade")) {
        selectedTower->upgrade(99);
      }
      if (ImGui::Button("Sell")) {
        level->sellTower(selectedTower);
        selectedTower = nullptr; // Clear selection after selling
      }
      ImGui::TreePop();
    }
  }
}

void SideMenu::renderStats() {
  // Code for the statistics section goes here

  ImGui::Text("HP: %d", level->getHealth());
  ImGui::Text("Money: %d", level->getCredits());
  ImGui::Text("Current Wave: %d", level->getCurrentWave());
}
