#include "PauseMenu.h"

PauseMenu::PauseMenu() { // any initialization
}
void PauseMenu::render(sf::RenderWindow &window, bool &isPaused) {
  sf::Vector2u windowSize = window.getSize();

  // Create semi-transparent dark rectangle
  sf::RectangleShape overlay(sf::Vector2f(windowSize.x, windowSize.y));
  overlay.setFillColor(sf::Color(0, 0, 0, 128));
  window.draw(overlay);

  // Center the pause menu
  ImGui::SetNextWindowPos(
      ImVec2((float)windowSize.x / 2, (float)windowSize.y / 2),
      ImGuiCond_Always, ImVec2(0.5f, 0.5f));

  ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);

  ImGui::Begin("Pause Menu", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

  ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));

  if (ImGui::Button("Resume", ImVec2(150, 50))) {
    isPaused = false;
  }
  if (ImGui::Button("Quit", ImVec2(150, 50))) {
    window.close();
  }

  ImGui::PopStyleVar(2);

  ImGui::End();
}
