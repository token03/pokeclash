#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
    : currentFrame_(0), frameDelay_(0), frameTimer_(0) {}

void AnimatedSprite::setFrames(const std::vector<sf::Texture> &textures) {
  for (const auto &texture : textures) {
    frames_.emplace_back(texture);
  }
}

void AnimatedSprite::setFrameDelay(float delay) { frameDelay_ = delay; }

void AnimatedSprite::update(float dt) {
  frameTimer_ += dt;

  if (frameTimer_ >= frameDelay_) {
    frameTimer_ = 0;
    currentFrame_ = (currentFrame_ + 1) % frames_.size();
  }
}

const sf::Sprite &AnimatedSprite::getSprite() const {
  return frames_[currentFrame_];
}
