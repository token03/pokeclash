#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Path {
public:
  Path();
  void draw(sf::RenderWindow &window);
  void addPoint(sf::Vector2f point);
  void addPoint(float x, float y);
  void clearPoints();
  sf::Vector2f getPoint(int index) const;
  int getNumPoints() const { return points.size(); }
  bool overlap(sf::Vector2f position, int radius);

private:
  std::vector<sf::Vector2f> points;
  int radius;
};
