#include "Path.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

Path::Path() {
  points.push_back(sf::Vector2f(50.0f, 50.0f));
  points.push_back(sf::Vector2f(50.0f, 250.0f));
  points.push_back(sf::Vector2f(250.0f, 250.0f));
  radius = 30;
}

void Path::draw(sf::RenderWindow &window) {
  if (points.size() < 2)
    return; // We need at least two points to draw a line

  for (size_t i = 0; i < points.size() - 1; ++i) {
    sf::Vertex line[] = {sf::Vertex(points[i], sf::Color::Red),
                         sf::Vertex(points[i + 1], sf::Color::Red)};
    window.draw(line, 2, sf::Lines);

    // Draw rectangle (aura)
    sf::Vector2f point1 = points[i];
    sf::Vector2f point2 = points[i + 1];

    // Find the angle (rotation) and length (size) of the line segment
    float dx = point2.x - point1.x;
    float dy = point2.y - point1.y;
    float angle = std::atan2(dy, dx) * 180.f / M_PI; // Convert to degrees
    float length = std::sqrt(dx * dx + dy * dy);

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(length, 2.f * radius));
    rectangle.setFillColor(
        sf::Color(255, 165, 0, 64)); // Orange color with transparency
    rectangle.setOrigin(0.f,
                        radius); // Center the rectangle on the line segment
    rectangle.setPosition(point1);
    rectangle.setRotation(angle);

    window.draw(rectangle);
  }
}

void Path::addPoint(sf::Vector2f point) { points.push_back(point); }

void Path::addPoint(float x, float y) { points.push_back(sf::Vector2f(x, y)); }

sf::Vector2f Path::getPoint(int index) const {
  if (index >= 0 && index < (int)points.size()) {
    return points[index];
  }
  return sf::Vector2f(); // Return a zero vector if index is out of range
}

bool Path::overlap(sf::Vector2i point, int radius) {
  if (points.size() < 2)
    return false; // We need at least two points to draw a line

  // Iterate over each line segment in the path
  for (std::size_t i = 0; i < points.size() - 1; ++i) {
    const sf::Vector2f &point1 = points[i];
    const sf::Vector2f &point2 = points[i + 1];

    // Vector from point1 to the given point
    sf::Vector2f point1ToPoint(point.x - point1.x, point.y - point1.y);

    // Vector from point1 to point2
    sf::Vector2f point1ToPoint2(point2.x - point1.x, point2.y - point1.y);

    // Squared length of the line segment
    float lineSegmentLengthSquared = point1ToPoint2.x * point1ToPoint2.x +
                                     point1ToPoint2.y * point1ToPoint2.y;

    // Projection of point1ToPoint onto the line segment, clamped to [0, 1]
    float t = std::max(0.f, std::min(1.f, (point1ToPoint.x * point1ToPoint2.x +
                                           point1ToPoint.y * point1ToPoint2.y) /
                                              lineSegmentLengthSquared));

    // The closest point on the line segment
    sf::Vector2f closestPointOnSegment(point1.x + t * point1ToPoint2.x,
                                       point1.y + t * point1ToPoint2.y);

    // Vector from the given point to the closest point on the line segment
    sf::Vector2f pointToClosestPoint(closestPointOnSegment.x - point.x,
                                     closestPointOnSegment.y - point.y);

    // Calculate the actual distance to the closest point on the line segment
    float distance = std::sqrt(pointToClosestPoint.x * pointToClosestPoint.x +
                               pointToClosestPoint.y * pointToClosestPoint.y);

    // If the distance is less than the sum of the radius and pathRadius, then
    // they overlap
    if (distance <= radius + this->radius)
      return true;
  }
  return false;
}
