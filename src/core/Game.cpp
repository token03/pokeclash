#include "Game.h"
#include <filesystem>
using std::string;

Game::Game() : window(sf::VideoMode(800, 600), "Pokeclash"), isPaused(false) {
  std::cout << "Game constructor" << std::endl;
  window.setFramerateLimit(60);

  loadTextures();

  level = std::make_unique<Level>(window.getSize().x, window.getSize().y);

  resourceIndicator = std::make_unique<ResourceIndicator>(*level);

  bool initialized = ImGui::SFML::Init(window);
  if (!initialized) {
    // Handle the initialization failure
  }
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
    ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2, windowSize.y / 2),
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

  if (towerMenu_.has_value()) {
    towerMenu_->render();
  }

  level->draw(window);
  resourceIndicator->draw(window);

  // Render ImGui here
  ImGui::SFML::Render(window);

  window.display();
}

void Game::handleClick(sf::Vector2i position) {
  if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
    Tower *tower = level->getTowerAtPosition(position);
    if (tower) {
      towerMenu_ = TowerMenu(tower, level.get());
    } else {
      level->addTower(PokemonType::Charmander, position);
    }
  }
  if (towerMenu_.has_value() && !towerMenu_->isVisible()) {
    towerMenu_.reset();
  }
}

void Game::loadTextures() {
  string textureFolderPath = "../assets/textures/";

  for (const auto &entry :
       std::filesystem::directory_iterator(textureFolderPath)) {
    if (entry.is_directory()) {
      // Process each character's directory
      TextureManager::getInstance().loadAnimations(entry.path());

      // Rest of the code for creating animated sprite instances...
    } else {
      string filePath = entry.path().string();
      string filename = entry.path().stem().string();
      TextureManager::getInstance().loadTexture(filename, filePath);
    }
  }

  std::cout << "Textures and animations loaded!" << std::endl;
}
