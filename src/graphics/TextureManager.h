#pragma once
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <map>
#include <string>

struct AnimationData {
  std::string name;
  int index;
  int frameWidth;
  int frameHeight;
  std::vector<float> durations;
};

class TextureManager {
public:
  static TextureManager &getInstance();
  void loadTexture(const std::string &name, const std::string &filename);
  void loadAnimations(const std::filesystem::path &directory);
  void loadAnimationData(const std::string &key, const pugi::xml_node &node);
  AnimationData &getAnimationData(const std::string &animation);
  sf::Texture &getRef(const std::string &texture);

private:
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, AnimationData> animationData;
  TextureManager() {}
  TextureManager(TextureManager const &) = delete;
  void operator=(TextureManager const &) = delete;
};
