#pragma once
#include<SFML\System.hpp>
#include<iostream>

class MapTile {
  public:
    // Constructor and Destructor
    MapTile(std::string tileType, float x, float y, bool isPassable);
    ~MapTile() = default;

    // Setters and Getters
    void setType(std::string tileType);
    void setPassable(bool isPassable);
    std::string getType();
    sf::Vector2f getTilePosition();
    bool getPassable();
 

  private:
  std::string _tileType;
  sf::Vector2f _tilePosition;
  bool _isPassable;
};