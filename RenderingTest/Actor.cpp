#include "Actor.h"

Actor::Actor(float posX, float posY, float dirX, float dirY) {
  this->_position = sf::Vector2f(posX, posY);
  this->_direction = sf::Vector2f(dirX, dirY);
}

sf::Vector2f Actor::getPosition() {
  return _position;
}

sf::Vector2f Actor::getDirection() {
  return _direction;
}

void Actor::setPosition(float posX, float posY) {
  this->_position = sf::Vector2f(posX, posY);
}

void Actor::setDirection(float dirX, float dirY) {
  this->_direction = sf::Vector2f(dirX, dirY);
}
