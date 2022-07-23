#include "BlinkyGhost.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <iostream>
#include "PacMan.h"
#include "GlobalManager.h"
#include "Map.h"
#include "Ghost.h"

game::BlinkyGhost::BlinkyGhost()
{
    loadSprites();
    actualGhost = ghostSprites[0];
    setInitialGhost();

    direction = 'D';
    spriteChangeInterval = 0.1f;
    actualGhostSpriteIndex = 0;
    findPath(findTargetPoint());
    changeDirection();
}

void game::BlinkyGhost::loadSprites()
{
    ghostTextures[0].loadFromFile("Sprites//ghosts//b-0.png");
    ghostTextures[1].loadFromFile("Sprites//ghosts//b-1.png");

    ghostSprites[0].setTexture(ghostTextures[0]);
    ghostSprites[1].setTexture(ghostTextures[1]);
}

void game::BlinkyGhost::setInitialGhost()
{
    setGhostOrigin();
    float posX = game::GlobalManager::getMapPos().x + game::GlobalManager::getTileSize() * 2.5;
    float posY = game::GlobalManager::getMapPos().y + game::GlobalManager::getTileSize() * 1.5;
    spawnPoint = sf::Vector2f(posX, posY);
    actualGhost.setPosition(spawnPoint);
}

void game::BlinkyGhost::movement()
{
    changeDirection();

    float elapsedTime = movementClock.getElapsedTime().asSeconds();
    movementClock.restart();
    float newPosX = actualGhost.getPosition().x;
    float newPosY = actualGhost.getPosition().y;
    float posX = actualGhost.getPosition().x;
    float posY = actualGhost.getPosition().y;
    int pathSize = path.size();

    if(direction == 'W')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(!((game::Map::getTileMapElement(actualTile.y - 1, actualTile.x) == "W" || indexInPath == pathSize - 1) && posY <= limitY))
        {
            newPosX = posX;
            newPosY = posY - speed * elapsedTime;
        }
    }
    else if(direction == 'S')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(!((game::Map::getTileMapElement(actualTile.y + 1, actualTile.x) == "W" || indexInPath == pathSize - 1) && posY >= limitY))
        {
            newPosX = posX;
            newPosY = posY + speed * elapsedTime;
        }
    }
    else if(direction == 'A')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(!((game::Map::getTileMapElement(actualTile.y, actualTile.x - 1) == "W" || indexInPath == pathSize - 1) && posX <= limitX))
        {
            newPosX = posX - speed * elapsedTime;
            newPosY = posY;
        }
    }
    else if(direction == 'D')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(!((game::Map::getTileMapElement(actualTile.y, actualTile.x + 1) == "W" || indexInPath == pathSize - 1) && posX >= limitX))
        {
            newPosX = posX + speed * elapsedTime;
            newPosY = posY;
        }
    }

    float spriteChangeElapsedTime = spriteChangeClock.getElapsedTime().asSeconds();
    if(spriteChangeElapsedTime >= spriteChangeInterval)
    {
        //when we change sprite we also recalculate path so we don t need to recalculate it every frame; we do it here istead of doing it on the end of this if cuz when we
        //change the sprite for actualGhost the actualGhost position will change and it will be (0, 0)
        if(mode == "Chase")
            findPath(findTargetPoint());
        else if(mode == "Frightened")
            findPath(findFrightenedTargetPoint());

        spriteChangeClock.restart();
        changeSprite();
    }

    timeInFrigthened = frightenedClock.getElapsedTime().asSeconds();
    if(timeInFrigthened >= frigthenedTime)
    {
        mode = "Chase";
        frightenedClock.restart();
    }

    setGhostOrigin();
    actualGhost.setPosition(sf::Vector2f(newPosX, newPosY));
    checkCollision();
}

sf::Sprite& game::BlinkyGhost::getActualGhost()
{
    return actualGhost;
}

void game::BlinkyGhost::changeDirection()
{
    sf::Vector2f actualPosition = getActualPosition();
    float posX = actualGhost.getPosition().x;
    float posY = actualGhost.getPosition().y;
    float limitX = game::GlobalManager::getMapPos().x + actualPosition.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2; //when its checking the next tile in path
    float limitY = game::GlobalManager::getMapPos().y + actualPosition.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;

    int pathSize = path.size();
    if(direction == 'W' && posY < limitY)
    {
        if(indexInPath + 1 >= pathSize)
        {
            // std::cout<<"TINA ATINSA"<<std::endl;
            return;
        }
        else
        {
            if(path[indexInPath + 1].first > path[indexInPath].first)
            {
                direction = 'S';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].second > path[indexInPath].second)
            {
                direction = 'D';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].second < path[indexInPath].second)
            {
                direction = 'A';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }

            if(actualPosition.x == path[indexInPath + 1].second && actualPosition.y == path[indexInPath + 1].first)
                indexInPath++;
        }
    }
    else if(direction == 'S' && posY > limitY)
    {
        if(indexInPath + 1 >= pathSize)
        {
            //  std::cout<<"TINA ATINSA"<<std::endl;
            return;
        }
        else
        {
            if(path[indexInPath + 1].first < path[indexInPath].first)
            {
                direction = 'W';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].second > path[indexInPath].second)
            {
                direction = 'D';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].second < path[indexInPath].second)
            {
                direction = 'A';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }

            if(actualPosition.x == path[indexInPath + 1].second && actualPosition.y == path[indexInPath + 1].first)
                indexInPath++;
        }
    }
    else if(direction == 'A' && posX < limitX)
    {
        if(indexInPath + 1 >= pathSize)
        {
            //  std::cout<<"TINA ATINSA"<<std::endl;
            return;
        }
        else
        {
            if(path[indexInPath + 1].first > path[indexInPath].first)
            {
                direction = 'S';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].first < path[indexInPath].first)
            {
                direction = 'W';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].second > path[indexInPath].second)
            {
                direction = 'D';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }

            if(actualPosition.x == path[indexInPath + 1].second && actualPosition.y == path[indexInPath + 1].first)
                indexInPath++;
        }
    }
    else if(direction == 'D' && posX > limitX)
    {
        if(indexInPath + 1 >= pathSize)
        {
            //  std::cout<<"TINA ATINSA"<<std::endl;
            return;
        }
        else
        {
            if(path[indexInPath + 1].first > path[indexInPath].first)
            {
                direction = 'S';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].first < path[indexInPath].first)
            {
                direction = 'W';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }
            else if(path[indexInPath + 1].second < path[indexInPath].second)
            {
                direction = 'A';
                actualGhost.setPosition(sf::Vector2f(limitX, limitY));
            }

            if(actualPosition.x == path[indexInPath + 1].second && actualPosition.y == path[indexInPath + 1].first)
                indexInPath++;
        }
    }
}

sf::Vector2f game::BlinkyGhost::findTargetPoint()
{
    float posY = game::PacMan::getActualPosition().y;
    float posX = game::PacMan::getActualPosition().x;

    return sf::Vector2f(posY, posX);
}

void game::BlinkyGhost::toSpawnPoint()
{
    actualGhost.setPosition(spawnPoint);
    direction = 'D';
}
