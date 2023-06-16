#include "ResourceIndicator.h"

ResourceIndicator::ResourceIndicator(Level &level) : level(level) {
  if (!font.loadFromFile("../assets/fonts/pokemon.ttf")) {
    // handle error
  }
  healthText.setFont(font);
  healthText.setCharacterSize(24);
  healthText.setFillColor(sf::Color::Red);
  healthText.setPosition(600, 30);
  healthText.setOutlineColor(sf::Color::White);
  healthText.setOutlineThickness(1);

  creditsText.setFont(font);
  creditsText.setCharacterSize(24);
  creditsText.setFillColor(sf::Color::Blue);
  creditsText.setPosition(600, 54);
  creditsText.setOutlineColor(sf::Color::White);
  creditsText.setOutlineThickness(1);
}

void ResourceIndicator::draw(sf::RenderWindow &window) {
  healthText.setString("Health: " + std::to_string(level.getHealth()));
  window.draw(healthText);
  creditsText.setString("Credits: " + std::to_string(level.getCredits()));
  window.draw(creditsText);
}
