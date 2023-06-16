#include "Pokemon.h"

Pokemon::Pokemon(sf::Vector2f pos)
    : position(pos), direction(Direction::South) {}

void Pokemon::setPosition(const sf::Vector2f &pos) { position = pos; }
