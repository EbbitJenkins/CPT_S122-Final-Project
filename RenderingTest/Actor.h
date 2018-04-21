#pragma once
#include <SFML\System.hpp>

class Actor {
  public:
    Actor() = default;
    Actor(float posX, float posY, float dirX, float dirY);
    ~Actor() = default;

    sf::Vector2f getPosition();
    sf::Vector2f getDirection();
    void setPosition(float posX, float posY);
    void setDirection(float dirX, float dirY);


  private:
    sf::Vector2f _position;
    sf::Vector2f _direction;
};