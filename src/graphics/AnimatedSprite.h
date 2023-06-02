#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class AnimatedSprite {
public:
  AnimatedSprite();

  void setFrames(const std::vector<sf::Texture> &textures);
  void setFrameDelay(float delay);

  void update(float dt);

  const sf::Sprite &getSprite() const;

private:
  std::vector<sf::Sprite> frames_;
  int currentFrame_;
  float frameDelay_;
  float frameTimer_;
};
