#pragma once

#include "TextureManager.h"
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

enum class Direction {
  South,
  SouthEast,
  East,
  NorthEast,
  North,
  NorthWest,
  West,
  SouthWest,
};

enum class AnimationState { FORWARD, BACKWARD };

class AnimatedSprite {
public:
  AnimatedSprite() = default;
  AnimatedSprite(const std::string &name);
  void setSpriteSheet(const std::string &key);
  void loadAnimationData(const std::string &key);
  void setFrameDelay(float delay) { frameDelay_ = delay; }
  void update(float dt, Direction dir);
  void draw(sf::RenderWindow &window, Direction dir);
  void setPosition(const sf::Vector2f &pos);
  sf::Vector2f getPosition() const { return position_; }
  sf::IntRect getRect() const;
  std::string getName() const { return name; }

private:
  AnimationState state_;
  std::string name;
  sf::Texture spriteSheet_;
  sf::Sprite sprite_;
  int frameWidth_;
  int frameHeight_;
  std::vector<float> durations_;
  int maxFrames_;
  int currentFrame_;
  float frameDelay_;
  float frameTimer_;
  sf::Vector2f position_;
};
