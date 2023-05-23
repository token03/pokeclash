#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../levels/Level.h"
#include "../entities/Tower.h"
#include "../entities/Mob.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Level level;
    Tower tower;  // This will become a list of towers in the real game
    Mob mob;  // This will become a list of mobs in the real game
};

#endif
