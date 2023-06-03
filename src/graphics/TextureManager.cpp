#include "TextureManager.h"
#include <iostream>

TextureManager &TextureManager::getInstance() {
  static TextureManager instance;
  return instance;
}

void TextureManager::loadTexture(const std::string &name,
                                 const std::string &filename) {
  // Create a new sf::Texture
  sf::Texture tex;

  // Try to load the texture from the file
  if (!tex.loadFromFile(filename)) {
    std::cerr << "Failed to load texture from file: " << filename << std::endl;
    return;
  }

  // If the texture was loaded successfully, store it in the map
  textures[name] = tex;
  std::cout << "Loaded texture from file: " << filename << std::endl;
}

sf::Texture &TextureManager::getRef(const std::string &texture) {
  /* Retrieve a texture from the map by its name. */
  return this->textures.at(texture);
}
