#ifndef MOB_H
#define MOB_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Mob {
public:
  Mob(float posX, float posY); // change int to float here
  void draw(sf::RenderWindow &window);
  sf::Vector2f getPosition() const;
  void update();

private:
  sf::Vector2f position;
  sf::CircleShape shape;
  float speed;
  float health;
  float size;
};

#endif
