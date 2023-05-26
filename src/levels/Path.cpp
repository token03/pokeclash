#include "Path.h"

Path::Path() {
  points.push_back(sf::Vector2f(50.0f, 50.0f));
  points.push_back(sf::Vector2f(50.0f, 250.0f));
  points.push_back(sf::Vector2f(250.0f, 250.0f));
}

void Path::draw(sf::RenderWindow &window) {
  if (points.size() < 2)
    return; // We need at least two points to draw a line

  for (size_t i = 0; i < points.size() - 1; ++i) {
    sf::Vertex line[] = {sf::Vertex(points[i], sf::Color::Red),
                         sf::Vertex(points[i + 1], sf::Color::Red)};

    window.draw(line, 2, sf::Lines);
  }
}

void Path::addPoint(sf::Vector2f point) { points.push_back(point); }

void Path::addPoint(float x, float y) { points.push_back(sf::Vector2f(x, y)); }

void Path::clearPoints() { points.clear(); }

sf::Vector2f Path::getPoint(int index) const {
  if (index >= 0 && index < points.size()) {
    return points[index];
  }
  return sf::Vector2f(); // Return a zero vector if index is out of range
}

int Path::getNumPoints() const { return points.size(); }
