#include "Game.h"
#include <filesystem>
using std::string;
;

Game::Game() : window(sf::VideoMode(1000, 700), "Pokeclash"), isPaused(false) {

  window.setFramerateLimit(60);
  loadTextures();
  loadImgui();

  level = std::make_unique<Level>(window.getSize().x, window.getSize().y);
  sideMenu.emplace(window, level);

  resourceIndicator = std::make_unique<ResourceIndicator>(*level);
}

void Game::loadImgui() {

  bool initialized = ImGui::SFML::Init(window);
  if (!initialized) {
    std::cout << "Failed to initialize ImGui.\n";
  }

  ImGuiStyle &style = ImGui::GetStyle();
  ImGui::StyleColorsLight(&style); // Apply the modified style
  style.Colors[ImGuiCol_Button] =
      ImVec4(0.8f, 0.2f, 0.2f, 1.0f); // Button color (red)
  style.Colors[ImGuiCol_ButtonHovered] =
      ImVec4(1.0f, 0.4f, 0.4f, 1.0f); // Button hover color (light red)
  style.Colors[ImGuiCol_ButtonActive] =
      ImVec4(1.0f, 0.6f, 0.6f, 1.0f); // Button pressed color (pale red)

  style.FramePadding = ImVec2(8, 4); // Adjust the padding around the button
  style.FrameRounding = 4.0f; // Adjust the rounding of the button corners
  style.ButtonTextAlign =
      ImVec2(0.5f, 0.5f);    // Adjust the alignment of the button text
  style.ScaleAllSizes(1.3f); // Scale all sizes by a factor of 1.1
}

void Game::run() {
  sf::Clock clock;
  sf::Clock imguiClock; // separate clock for ImGui
  while (window.isOpen()) {
    processEvents();

    // update ImGui
    ImGui::SFML::Update(window, imguiClock.restart());

    float dt = clock.restart().asSeconds();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    switch (event.type) {
    case sf::Event::Closed:
      window.close();
      break;
    case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        handleClick(position);
      }
      break;
    case sf::Event::KeyPressed:
      if (event.key.code == sf::Keyboard::P) {
        isPaused = !isPaused;
      }
      break;
    case sf::Event::Resized:
    case sf::Event::LostFocus:
    case sf::Event::GainedFocus:
    case sf::Event::TextEntered:
    case sf::Event::KeyReleased:
    case sf::Event::MouseWheelMoved:
    case sf::Event::MouseWheelScrolled:
    case sf::Event::MouseButtonReleased:
    case sf::Event::MouseMoved:
    case sf::Event::MouseEntered:
    case sf::Event::MouseLeft:
    case sf::Event::TouchBegan:
    case sf::Event::TouchMoved:
    case sf::Event::TouchEnded:
    case sf::Event::SensorChanged:
    case sf::Event::Count:
      break;
    }
  }
}

Game::~Game() {
  // Shutdown ImGui
  ImGui::SFML::Shutdown();
}

void Game::update(float dt) {
  if (!isPaused) {
    level->update(dt);
  }
}

void Game::render() {
  window.clear(sf::Color::White);

  level->draw(window);
  resourceIndicator->draw(window);

  if (isPaused) {
    pauseMenu.render(window, isPaused);
  } else {
    sideMenu->render(); // Render the side menu
  }

  ImGui::SFML::Render(window);

  window.display();
}

void Game::handleClick(sf::Vector2i position) {
  if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
    sf::Vector2f worldPos = window.mapPixelToCoords(position);
    auto currentPokemonToPlace = sideMenu->getCurrentPokemonToPlace();
    if (currentPokemonToPlace.has_value() &&
        level->validTowerPlacement(worldPos, 5)) {
      std::cout << "Attempting to place a tower.\n"; // Place a tower here
      level->addTower(currentPokemonToPlace.value(), worldPos);
      sideMenu->resetCurrentPokemonToPlace();
      sideMenu->setSelectedTower(level->getTowerAtPosition(worldPos));
    } else {
      Tower *tower = level->getTowerAtPosition(worldPos);
      if (tower) {
        sideMenu->setSelectedTower(tower);
      }
    }
  }
  if (sideMenu->getSelectedTower() == nullptr) {
    sideMenu->reset();
  }
}

void Game::loadTextures() {
  string textureFolderPath = "../assets/textures/";

  for (const auto &subDirectory :
       std::filesystem::directory_iterator(textureFolderPath)) {
    if (subDirectory.is_directory()) {
      string subDirName = subDirectory.path().filename().string();
      string subFolderPath = subDirectory.path().string();

      if (subDirName == "pokemon") {
        for (const auto &entry :
             std::filesystem::directory_iterator(subFolderPath)) {
          if (entry.is_directory()) {
            TextureManager::getInstance().loadAnimations(entry.path());
          } else {
            string filePath = entry.path().string();
            string filename = entry.path().stem().string();
            TextureManager::getInstance().loadTexture(filename, filePath);
          }
        }
      } else if (subDirName == "projectiles") {
        for (const auto &entry :
             std::filesystem::directory_iterator(subFolderPath)) {
        }
      } else if (subDirName == "icons") {
      }
    }
  }

  std::cout << "Textures and animations loaded!" << std::endl;
}
