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
  void update(float dt, Direction dir);
  void draw(sf::RenderWindow &window, Direction dir);
  void setPosition(const sf::Vector2f &pos);
  void setOrigin(int radius);
  void setAttackSpeed(float attacksPerSecond);
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
  std::vector<float> scaledDurations_;
  int maxFrames_;
  int currentFrame_;
  float frameTimer_;
  sf::Vector2f position_;
};
