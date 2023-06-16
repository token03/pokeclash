#include "AnimatedSprite.h"
#include "TextureManager.h"
#include <iostream>
#include <string>

AnimatedSprite::AnimatedSprite(const std::string &name)
    : currentFrame_(0), frameDelay_(0.2f), frameTimer_(0), name(name) {
  setSpriteSheet(name);
  loadAnimationData(name);

  if (frameWidth_ == 0 || frameHeight_ == 0) {
    std::cerr << "Error: No frames were loaded for animation " << name << "\n";
  }
  // Set scale and origin only once here
  sprite_.setScale(2, 2);
  sprite_.setOrigin(frameWidth_, frameHeight_);
}

void AnimatedSprite::setSpriteSheet(const std::string &key) {
  spriteSheet_ = TextureManager::getInstance().getRef(key);

  // Check if the sprite sheet has been loaded properly
  if (spriteSheet_.getSize().x == 0 || spriteSheet_.getSize().y == 0) {
    std::cerr << "Error: Failed to load sprite sheet for key " << key << "\n";
  }
  sprite_.setTexture(spriteSheet_); // Set texture only once here
}

void AnimatedSprite::loadAnimationData(const std::string &key) {
  const AnimationData &data =
      TextureManager::getInstance().getAnimationData(key);
  frameWidth_ = data.frameWidth;
  frameHeight_ = data.frameHeight;
  for (int i = 0; i < data.durations.size(); i++) {
    durations_.push_back(data.durations[i] / 100);
    std::cout << "Duration: " << durations_[i] << "\n";
  }
  maxFrames_ = spriteSheet_.getSize().x / frameWidth_;
  std::cout << "Frame Size: " << frameWidth_ << " " << frameHeight_ << "\n";
  sprite_.setTexture(spriteSheet_);
}

void AnimatedSprite::update(float dt, Direction dir) {
  frameTimer_ += dt;
  if (frameTimer_ >= durations_[currentFrame_]) {
    if (currentFrame_ >= maxFrames_ - 1) {
      currentFrame_ = 0;
    } else {
      ++currentFrame_;
    }
    frameTimer_ = 0.f;
  }
}

void AnimatedSprite::draw(sf::RenderWindow &window, Direction direction) {
  sf::IntRect currentRect_(currentFrame_ * frameWidth_,
                           static_cast<int>(direction) * frameHeight_,
                           frameWidth_, frameHeight_);
  sprite_.setTextureRect(currentRect_); // Only set texture rect here

  // Set position considering scale
  sprite_.setPosition(position_.x + frameWidth_, position_.y + frameHeight_);

  window.draw(sprite_);
}

void AnimatedSprite::setPosition(const sf::Vector2f &pos) { position_ = pos; }

sf::IntRect AnimatedSprite::getRect() const {
  return sf::IntRect(currentFrame_ * frameWidth_, 0, frameWidth_, frameHeight_);
}
