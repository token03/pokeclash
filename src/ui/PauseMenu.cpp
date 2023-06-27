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

  // Backup current style
  ImVec4 buttonTextColor = ImGui::GetStyle().Colors[ImGuiCol_Button];
  ImVec2 buttonAlign = ImGui::GetStyle().ButtonTextAlign;

  // Set new style
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // white
  ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign,
                      ImVec2(0.5f, 0.5f)); // center text

  // Backup current font size
  ImFont *font = ImGui::GetFont();
  float oldFontSize = font->Scale;

  // Set new font size
  font->Scale = oldFontSize * 2.f; // Increase font size by 50%
  ImGui::PushFont(font);

  ImGui::SetCursorPos(ImVec2(25, 50)); // center buttons

  if (ImGui::Button("Resume", ImVec2(150, 50))) {
    isPaused = false;
  }
  ImGui::SetCursorPos(ImVec2(25, 115)); // center buttons

  if (ImGui::Button("Quit", ImVec2(150, 50))) {
    window.close();
  }

  // Restore the original font size
  ImGui::PopFont();
  font->Scale = oldFontSize;

  ImGui::PopStyleVar(1);
  ImGui::PopStyleColor();                          // restore button text color
  ImGui::GetStyle().ButtonTextAlign = buttonAlign; // restore text alignment

  ImGui::End();
}
