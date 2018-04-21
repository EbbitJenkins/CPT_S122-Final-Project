#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Main.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include "Player.h"

const char worldMap[5][8] =
{
  '#','#','#','#','#',
  '#','.','.','.','#',
  '#','.','.','.','#',
  '#','.','#','.','#',
  '#','.','.','.','#',
  '#','.','.','.','#',
  '#','#','.','#','#',
  '#','#','#','#','#'
};

int main(void) {
  Player firstPlayer;
  firstPlayer.setPosition(1.0f, 1.0f);
  firstPlayer.setDirection(1.0f, 0.0f);

  sf::Vector2f plane(0.0f, 0.66f);

  sf::Image weapon;
  weapon.loadFromFile("weapon.png");
  weapon.createMaskFromColor(sf::Color::White);

  sf::Texture weaponTexture;
  weaponTexture.loadFromImage(weapon);

  sf::Sprite weaponSprite;
  weaponSprite.setTexture(weaponTexture);

  weaponSprite.setScale(sf::Vector2f(0.5f, 0.2f));
  weaponSprite.setRotation(-210.0f);
  weaponSprite.setPosition(sf::Vector2f(600, 500));

  sf::RenderWindow mainWindow(sf::VideoMode(801, 600), "Testing");
  mainWindow.setSize(sf::Vector2u(800, 600));
  mainWindow.setFramerateLimit(60);

  sf::VertexArray walls(sf::Lines, 18 * 800);

  // Main loop
  while (mainWindow.isOpen()) {
    walls.resize(0);
    for (int x = 0; x < 800; x++) {
      float cameraX = ((2 * x) / float(800) - 1);
      sf::Vector2f rayDir = firstPlayer.getDirection() + plane * cameraX;
      sf::Vector2i mapPos((int)firstPlayer.getPosition().x, (int)firstPlayer.getPosition().y);
      sf::Vector2f sideDist;
      sf::Vector2f deltaDist(sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
                             sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)));
      float perpWallDist = 0.0f;


      sf::Clock clock;
      float dt = clock.restart().asSeconds();

      sf::Event event;
      while (mainWindow.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            mainWindow.close();
            break;
          default:
            break;
        }
      }


      sf::Vector2i step;
      char tile = '.';

      int hit = 0;
      int side;

      if (rayDir.x < 0.0f) {
        step.x = -1;
        sideDist.x = (firstPlayer.getPosition().x - mapPos.x) * deltaDist.x;
      } else {
        step.x = 1;
        sideDist.x = (mapPos.x + 1.0f - firstPlayer.getPosition().x) * deltaDist.x;
      }
      if (rayDir.y < 0.0f) {
        step.y = -1;
        sideDist.y = (firstPlayer.getPosition().y - mapPos.y) * deltaDist.y;
      } else {
        step.y = 1;
        sideDist.y = (mapPos.y + 1.0f - firstPlayer.getPosition().y) * deltaDist.y;
      }



      int drawStart;
      int drawEnd;

      int ceilingPixel = 0;
      int groundPixel = 0;

      while (tile == '.') {
        if (sideDist.x < sideDist.y) {
          sideDist.x += deltaDist.x;
          mapPos.x += step.x;
          side = 0;
        } else {
          sideDist.y += deltaDist.y;
          mapPos.y += step.y;
          side = 1;
        }
        if (worldMap[mapPos.x][mapPos.y] == '#') {
          hit = 1;
        }
        if (side == 0) {
          perpWallDist = (mapPos.x - firstPlayer.getPosition().x + (1 - step.x) / 2) / rayDir.x;
        } else {
          perpWallDist = (mapPos.y - firstPlayer.getPosition().y + (1 - step.y) / 2) / rayDir.y;
        }



        int lineHeight = (int)(600 / perpWallDist);

        //       int drawStart = lineHeight / (2 + 300);
        //        if (drawStart < 0) {
        //          drawStart = 0;
        //        } 
        //        int drawEnd = lineHeight / (2 + 300);
        //        if (drawEnd >= 600) {
        //         drawEnd = 600 - 1;
        //     }
        

        

        

        walls.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), sf::Color::Blue));
        groundPixel = int(lineHeight * (0.66f + 600) * 0.5);
        walls.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), sf::Color::Blue));

        walls.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), sf::Color::Red));
        ceilingPixel = int(-lineHeight * (1.0f - 0.66f) + 600 * 0.5f);
        walls.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), sf::Color::Red));

      }
      tile = worldMap[mapPos.x][mapPos.y];


      sf::Color col = sf::Color::White;
      if (side == 1) {
        col.r /= 2;
        col.g /= 2;
        col.b /= 2;
      }

        drawStart = ceilingPixel;
        drawEnd = groundPixel;

        walls.append(sf::Vertex(sf::Vector2f((float)x, (float)drawStart), col));
        walls.append(sf::Vertex(sf::Vector2f((float)x, (float)drawEnd), col));


        

        float rotationSpeed = 0.0001f;
        float moveSpeed = 5.0f;

        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          float oldDirX = rayDir.x;
          rayDir.x = rayDir.x * cos(-rotationSpeed) - rayDir.y * sin(-rotationSpeed);
          rayDir.y = oldDirX * sin(-rotationSpeed) + rayDir.y * cos(-rotationSpeed);
          float oldPlaneX = plane.x;
          plane.x = plane.x * cos(-rotationSpeed) - plane.y * sin(-rotationSpeed);
          plane.y = oldPlaneX * sin(-rotationSpeed) + plane.y * cos(-rotationSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          float oldDirX = rayDir.x;
          rayDir.x = rayDir.x * cos(rotationSpeed) - rayDir.y * sin(rotationSpeed);
          rayDir.y = oldDirX * sin(rotationSpeed) + rayDir.y * cos(rotationSpeed);
          float oldPlaneX = plane.x;
          plane.x = plane.x * cos(rotationSpeed) - plane.y * sin(rotationSpeed);
          plane.y = oldPlaneX * sin(rotationSpeed) + plane.y * cos(rotationSpeed);
        }
        
      }
      mainWindow.clear();
      mainWindow.draw(walls);
      mainWindow.draw(weaponSprite);
      mainWindow.display();
    }
 
}