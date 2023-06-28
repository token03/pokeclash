#include "SideMenu.h"

SideMenu::SideMenu(sf::RenderWindow &window, std::unique_ptr<Level> &level)
    : window(window), level(level) {}

void SideMenu::render() {
  ImGui::SetNextWindowPos(ImVec2(window.getSize().x * 0.85f, 0),
                          ImGuiCond_Always);
  ImGui::SetNextWindowSize(
      ImVec2(window.getSize().x * 0.15f, window.getSize().y), ImGuiCond_Always);

  ImGui::Begin("Side Menu", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove);

  // Backup current font size
  ImFont *font = ImGui::GetFont();
  float oldFontSize = font->Scale;

  // Set new font size
  font->Scale = oldFontSize * 1.2f; // Increase font size by 50%
  ImGui::PushFont(font);

  renderStats();
  ImGui::Separator();
  renderTowerPlacement();
  ImGui::Separator();
  renderTowerManagement();

  // Restore the original font size
  ImGui::PopFont();
  font->Scale = oldFontSize;

  ImGui::End();
}

void SideMenu::renderTowerPlacement() {
  TextureManager &tm = TextureManager::getInstance();
  ImGui::Columns(2, "mycolumns");

  ImTextureID charmanderIcon =
      reinterpret_cast<void *>(tm.getRef("CharmanderIcon").getNativeHandle());
  if (ImGui::ImageButton(charmanderIcon, ImVec2(32, 32))) {
    currentPokemonToPlace = "Charmander";
    std::cout << "Charmander selected for placement.\n";
  }
  ImGui::NextColumn();
  ImTextureID chimcharIcon =
      reinterpret_cast<void *>(tm.getRef("ChimcharIcon").getNativeHandle());
  if (ImGui::ImageButton(chimcharIcon, ImVec2(32, 32))) {
    currentPokemonToPlace = "Chimchar";
    std::cout << "Chimchar selected for placement.\n";
  }

  // Reset to 1 column so the layout goes back to normal.
  ImGui::Columns(1);
}

void SideMenu::renderTowerManagement() {
  if (selectedTower) {
    // Display tower information and controls
    ImGui::Text("Name: %s", selectedTower->getName().c_str());
    ImGui::Text("Level: %d", selectedTower->getLevel());
    ImGui::Text("Damage: %.2f", selectedTower->getDamage());
    ImGui::Text("Range: %.2f", selectedTower->getRange());
    ImGui::Text("(%i, %i)", (int)selectedTower->getPosition().x,
                (int)selectedTower->getPosition().y);

    if (ImGui::Button("Upgrade")) {
      selectedTower->upgrade(99);
    }
    if (ImGui::Button("Sell")) {
      level->sellTower(selectedTower);
      selectedTower = nullptr; // Clear selection after selling
    }
    ImGui::Separator();
  }
}

void SideMenu::renderStats() {
  // Code for the statistics section goes here
  ImGui::Text("Current Wave: %d", level->getCurrentWave());
}

void SideMenu::setSelectedTower(Tower *tower) { selectedTower = tower; }

Tower *SideMenu::getSelectedTower() { return selectedTower; }

void SideMenu::reset() { selectedTower = nullptr; }

void SideMenu::resetCurrentPokemonToPlace() {
  currentPokemonToPlace = std::nullopt;
}

std::optional<string> SideMenu::getCurrentPokemonToPlace() {
  return currentPokemonToPlace;
}
