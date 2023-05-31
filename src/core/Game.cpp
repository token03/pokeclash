#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Pokeclash"),
      level(window.getSize().x, window.getSize().y) {
  std::cout << "Game constructor" << std::endl;
  window.setFramerateLimit(60);

  // Initialize ImGui here
  ImGui::SFML::Init(window);
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
        level.addTower(position.x, position.y);
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
  level.update(dt);
}

void Game::render() {
  window.clear(sf::Color::White);

  // Add ImGui windows, buttons, etc. here
  ImGui::Begin("UI Window");
  if (ImGui::Button("Click me")) {
    std::cout << "Button clicked!" << std::endl;
  }
  ImGui::End();

  level.draw(window);

  // Render ImGui here
  ImGui::SFML::Render(window);

  window.display();
}

bool Game::isValidPlacement(int x, int y) {
  // TODO: Add more logic to check if the placement is valid.
  // For now, we only check if the tower is within the bounds of the level.
  return x >= 0 && y >= 0 && x < 800 && y < 600;
}
