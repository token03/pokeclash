#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Pokeclash"),
      level(window.getSize().x, window.getSize().y), isPaused(false) {
  std::cout << "Game constructor" << std::endl;
  window.setFramerateLimit(60);

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
        handleClick(position.x, position.y);
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
  // Here you'd update the game objects, for example move the mobs, make the
  // towers attack, etc.
  if (!isPaused) {
    level.update(dt);
  }
}

void Game::render() {
  window.clear(sf::Color::White);

  // Render the pause menu when paused
  if (isPaused) {

    sf::Vector2u windowSize = window.getSize();
    ImDrawList *drawList = ImGui::GetForegroundDrawList();

    drawList->AddRectFilled(ImVec2(0, 0), ImVec2(windowSize.x, windowSize.y),
                            IM_COL32(0, 0, 0, 128));
    ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2, windowSize.y / 2),
                            ImGuiCond_Once, ImVec2(0.5f, 0.5f));

    // Use ImGuiWindowFlags_NoTitleBar to disable the title bar
    ImGui::Begin("Pause Menu", nullptr, ImGuiWindowFlags_NoTitleBar);
    if (ImGui::Button("Resume")) {
      isPaused = false;
    }
    if (ImGui::Button("Quit")) {
      window.close();
    }
    ImGui::End();
  }

  // Render the tower menu if it exists
  if (towerMenu_.has_value()) {
    towerMenu_->render();
  }

  level.draw(window);

  // Render ImGui here
  ImGui::SFML::Render(window);

  window.display();
}

void Game::handleClick(int x, int y) {
  // Check if any ImGui window is being hovered over
  if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
    // If not, handle the click in the game
    Tower *tower = level.getTowerAtPosition(x, y);
    if (tower) {
      // If a tower was clicked, open the upgrade menu
      towerMenu_ = TowerMenu(tower);
    } else {
      // If no tower was clicked, add a new tower
      level.addTower(TowerType::Charmander, x, y);
    }
  }
}
