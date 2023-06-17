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
  renderTowerMenu();
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

void SideMenu::renderTowerMenu() {
  // Code for the tower management section goes here

  if (towerMenu_.has_value()) {
    towerMenu_->render();
  }
}

void SideMenu::renderStats() {
  // Code for the statistics section goes here

  ImGui::Text("HP: %d", level->getHealth());
  ImGui::Text("Money: %d", level->getCredits());
  ImGui::Text("Current Wave: %d", level->getCurrentWave());
}
