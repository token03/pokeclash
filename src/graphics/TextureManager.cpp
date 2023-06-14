#include "TextureManager.h"
#include <iostream>

using std::string;

TextureManager &TextureManager::getInstance() {
  static TextureManager instance;
  return instance;
}

void TextureManager::loadTexture(const string &name, const string &filename) {
  // Create a new sf::Texture
  sf::Texture tex;

  // Try to load the texture from the file
  if (!tex.loadFromFile(filename)) {
    std::cerr << "Failed to load texture from file: " << filename << std::endl;
    return;
  }

  // If the texture was loaded successfully, store it in the map
  textures[name] = tex;
  std::cout << "Loaded texture from file: " << name << std::endl;
}

sf::Texture &TextureManager::getRef(const string &texture) {
  /* Retrieve a texture from the map by its name. */
  if (textures.find(texture) == textures.end())
    std::cerr << "Failed to find texture: " << texture << std::endl;

  return this->textures.at(texture);
}

void TextureManager::loadAnimations(const std::filesystem::path &directory) {
  pugi::xml_document doc;

  // Load the character's XML file
  if (!doc.load_file((directory / "AnimData.xml").c_str())) {
    // Handle error...
    return;
  }

  // Process each animation file in the character's directory
  for (const auto &subentry : std::filesystem::directory_iterator(directory)) {
    if (subentry.is_regular_file() && subentry.path().extension() == ".png") {
      string stem = subentry.path().stem().string();
      if (stem.size() >= 5 && stem.substr(stem.size() - 5) == "-Anim") {
        // Load the texture
        string textureName =
            directory.stem().string() + stem.substr(0, stem.size() - 5);
        string filePath = subentry.path().string();
        loadTexture(textureName, filePath);

        // Get the animation name (omit "-Anim")
        string animationName = stem.substr(0, stem.size() - 5);

        // Get the corresponding animation data from the XML
        pugi::xml_node animNode =
            doc.child("AnimData")
                .child("Anims")
                .find_child([&](const pugi::xml_node &node) {
                  return node.child("Name").child_value() == animationName;
                });

        if (!animNode) {
          std::cerr << "Failed to find animation data for: " << animationName
                    << std::endl;
          continue;
        }

        // Load the animation data
        loadAnimationData(directory.stem().string() + animationName, animNode);
      }
    }
  }
}

void TextureManager::loadAnimationData(const string &key,
                                       const pugi::xml_node &node) {
  AnimationData animData;

  animData.name = node.child("Name").text().as_string();
  animData.frameWidth = node.child("FrameWidth").text().as_int();
  animData.frameHeight = node.child("FrameHeight").text().as_int();
  for (const auto &durations : node.child("Durations"))
    animData.durations.push_back(durations.text().as_float());

  // Extract other animation data from the node...

  // Store the animation data in the map
  animationData[key] = animData;

  std::cout << "Loaded animation data: " << key << std::endl;
  std::cout << "Frame width: " << animData.frameWidth << std::endl;
  std::cout << "Frame height: " << animData.frameHeight << std::endl;
  std::cout << "Name: " << animData.name << std::endl;
}

AnimationData &TextureManager::getAnimationData(const string &animation) {
  if (animationData.find(animation) == animationData.end())
    std::cerr << "Failed to find animation data for: " << animation
              << std::endl;
  return animationData.at(animation);
}
