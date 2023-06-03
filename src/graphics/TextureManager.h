#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
public:
  static TextureManager &getInstance();

  // Loads a texture from a file into the map if it hasn't already been loaded.
  void loadTexture(const std::string &name, const std::string &filename);

  // Retrieves a texture from the map by its name.
  sf::Texture &getRef(const std::string &texture);

private:
  // The map that links names to sf::Texture objects.
  std::map<std::string, sf::Texture> textures;

  // Private constructor and copy constructor for singleton pattern.
  TextureManager() {}
  TextureManager(TextureManager const &) = delete;
  void operator=(TextureManager const &) = delete;
};
