#include "MapTile.h"

MapTile::MapTile(std::string tileType, float x, float y, bool isPassable) {
  this->_tileType = tileType;
  this->_tilePosition = sf::Vector2f(x, y);
  this->_isPassable = isPassable;
}

void MapTile::setType(std::string tileType) {
  this->_tileType = tileType;
}


void MapTile::setPassable(bool isPassable) {
  this->_isPassable = isPassable;
}

std::string MapTile::getType() {
  return _tileType;
}

bool MapTile::getPassable() {
  return _isPassable;
}

sf::Vector2f MapTile::getTilePosition() {
  return _tilePosition;
}
