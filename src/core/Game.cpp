#include "Game.h"
#include <filesystem>
using std::string;
;

Game::Game() : window(sf::VideoMode(1000, 700), "Pokeclash"), isPaused(false) {
  window.setFramerateLimit(60);

  loadTextures();
  loadImgui();

  level = std::make_unique<Level>(window.getSize().x, window.getSize().y);

  resourceIndicator = std::make_unique<ResourceIndicator>(*level);
}

void Game::loadImgui() {

  bool initialized = ImGui::SFML::Init(window);
  if (!initialized) {
    // Handle the initialization failure
  }

  ImGuiStyle &style = ImGui::GetStyle();
  ImGui::StyleColorsLight(&style); // Apply the modified style

  // Modifying colors
  style.Colors[ImGuiCol_Button] =
      ImVec4(0.8f, 0.2f, 0.2f, 1.0f); // Button color (red)
  style.Colors[ImGuiCol_ButtonHovered] =
      ImVec4(1.0f, 0.4f, 0.4f, 1.0f); // Button hover color (light red)
  style.Colors[ImGuiCol_ButtonActive] =
      ImVec4(1.0f, 0.6f, 0.6f, 1.0f); // Button pressed color (pale red)

  // Modifying other properties
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

  if (isPaused) {
    sf::Vector2u windowSize = window.getSize();
    ImDrawList *drawList = ImGui::GetForegroundDrawList();

    drawList->AddRectFilled(ImVec2(0, 0), ImVec2(windowSize.x, windowSize.y),
                            IM_COL32(0, 0, 0, 128));
    ImGui::SetNextWindowPos(
        ImVec2((float)windowSize.x / 2, (float)windowSize.y / 2),
        ImGuiCond_Once, ImVec2(0.5f, 0.5f));

    ImGui::Begin("Pause Menu", nullptr, ImGuiWindowFlags_NoTitleBar);
    if (ImGui::Button("Resume")) {
      isPaused = false;
    }
    if (ImGui::Button("Quit")) {
      window.close();
    }
    ImGui::End();
  }

  level->draw(window);
  resourceIndicator->draw(window);

  renderSideMenu(); // Add this line

  ImGui::SFML::Render(window);

  window.display();
}

void Game::handleClick(sf::Vector2i position) {
  if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
    sf::Vector2f worldPos = window.mapPixelToCoords(position);
    if (currentPokemonToPlace.has_value()) {
      // Place a tower here
      level->addTower(currentPokemonToPlace.value(), worldPos);
      currentPokemonToPlace.reset(); // Reset after placing
    } else {
      Tower *tower = level->getTowerAtPosition(worldPos);
      if (tower) {
        towerMenu_ = TowerMenu(tower, level.get());
      }
    }
  }

  if (towerMenu_.has_value() && !towerMenu_->isVisible()) {
    towerMenu_.reset();
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
      }
    }
  }

  std::cout << "Textures and animations loaded!" << std::endl;
}

void Game::renderSideMenu() {
  ImGui::SetNextWindowPos(ImVec2(window.getSize().x * 0.85f, 0),
                          ImGuiCond_Always); // Set the position
  ImGui::SetNextWindowSize(
      ImVec2(window.getSize().x * 0.15f, window.getSize().y),
      ImGuiCond_FirstUseEver); // Set the size

  ImGui::Begin("Side Menu", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  ImGui::Text("HP: %d", level->getHealth());     // Display HP
  ImGui::Text("Money: %d", level->getCredits()); // Display money
  ImGui::Text("Current Wave: %d",
              level->getCurrentWave()); // Display current wave

  if (ImGui::Button("Place Charmander")) {
    // If Charmander is clicked
    currentPokemonToPlace = PokemonType::Charmander;
  }

  // Similarly, you can add more Pokemon options to place here

  // Tower management
  if (towerMenu_.has_value()) {
    towerMenu_->render();
  }

  ImGui::End();
}
