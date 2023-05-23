#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Tower Defense Game"),
      level(40, 40),
      tower(200, 200),
      mob(100, 100)
{
}

void Game::run()
{
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
    // Here you'd update the game objects, for example move the mobs, make the towers attack, etc.
}

void Game::render()
{
    window.clear();
    level.draw(window);
    mob.draw(window);
    tower.draw(window);
    window.display();
}
