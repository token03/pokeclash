#include "Game.h"
#include <SFML/Window/Mouse.hpp>
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Pokeclash"), level(40, 40) {
  std::cout << "Game constructor" << std::endl;
  window.setFramerateLimit(60);
  level.getTowers().emplace_back(200, 200);
  std::cout << "Tower added" << std::endl;
  level.getMobs().emplace_back(100, 100);
  std::cout << "Mob added" << std::endl;
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    processEvents();
    float dt = clock.restart().asSeconds();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::Closed:
      window.close();
      break;
    case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (isValidPlacement(position.x, position.y)) {
          level.getTowers().emplace_back(position.x, position.y);
        }
      }
      break;
    }
  }
}

void Game::update(float dt) {
  // Here you'd update the game objects, for example move the mobs, make the
  // towers attack, etc.
  level.update(dt);
}

void Game::render() {
  window.clear(sf::Color::White);
  level.draw(window);
  window.display();
}

bool Game::isValidPlacement(int x, int y) {
  // TODO: Add more logic to check if the placement is valid.
  // For now, we only check if the tower is within the bounds of the level.
  return x >= 0 && y >= 0 && x < 800 && y < 600;
}
