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
    speed = 150;
    spriteChangeInterval = 0.1f;
    actualGhostSpriteIndex = 0;
    findPath();
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
    float posX = game::GlobalManager::getMapPos().x + game::GlobalManager::getTileSize() * 1.5;
    float posY = game::GlobalManager::getMapPos().y + game::GlobalManager::getTileSize() * 1.5;
    actualGhost.setPosition(sf::Vector2f(posX, posY));
}

void game::BlinkyGhost::movement()
{
    changeDirection();

    float elapsedTime = movementClock.getElapsedTime().asSeconds();
    movementClock.restart();
    float newPosX, newPosY;
    float posX = actualGhost.getPosition().x;
    float posY = actualGhost.getPosition().y;
    int pathSize = path.size();

    if(direction == 'W')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if((game::Map::getTileMapElement(actualTile.y - 1, actualTile.x) == "W" || indexInPath == pathSize - 1) && posY <= limitY)
            return;

        newPosX = posX;
        newPosY = posY - speed * elapsedTime;
    }
    else if(direction == 'S')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if((game::Map::getTileMapElement(actualTile.y + 1, actualTile.x) == "W" || indexInPath == pathSize - 1) && posY >= limitY)
            return;

        newPosX = posX;
        newPosY = posY + speed * elapsedTime;
    }
    else if(direction == 'A')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if((game::Map::getTileMapElement(actualTile.y, actualTile.x - 1) == "W" || indexInPath == pathSize - 1) && posX <= limitX)
            return;

        newPosX = posX - speed * elapsedTime;
        newPosY = posY;
    }
    else if(direction == 'D')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if((game::Map::getTileMapElement(actualTile.y, actualTile.x + 1) == "W" || indexInPath == pathSize - 1) && posX >= limitX)
            return;

        newPosX = posX + speed * elapsedTime;
        newPosY = posY;
    }

    float spriteChangeElapsedTime = spriteChangeClock.getElapsedTime().asSeconds();
    if(spriteChangeElapsedTime >= spriteChangeInterval)
    {
        findPath();   //when we change sprite we also recalculate path so we don t need to recalculate it every frame; we do it here istead of doing it on the end of this if cuz when we
        //change the sprite for actualGhost the actualGhost position will change and it will be (0, 0)

        spriteChangeClock.restart();
        if(actualGhostSpriteIndex == 0)
            actualGhostSpriteIndex = 1;
        else
            actualGhostSpriteIndex = 0;

        actualGhost = ghostSprites[actualGhostSpriteIndex];
    }

    setGhostOrigin();
    actualGhost.setPosition(sf::Vector2f(newPosX, newPosY));
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



void game::BlinkyGhost::findPath()
{
    int dl[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for(int i = 0; i < 31; i++)
        for(int j = 0; j < 28; j++)
            pathMatrix[i][j] = 0;

    pathMatrix[(int) getActualPosition().y][(int) getActualPosition().x] = 1;

    std::queue<std::pair<int, int>> coada;
    coada.push(std::make_pair(getActualPosition().y, getActualPosition().x));

    int x, y, xx, yy;
    while(!coada.empty())
    {
        y = coada.front().first;
        x = coada.front().second;

        for(int i = 0; i < 4; i++)
        {
            xx = x + dc[i];
            yy = y + dl[i];
            if((game::Map::getTileMapElement(yy, xx) == "O" || game::Map::getTileMapElement(yy, xx) == "G") && pathMatrix[yy][xx] == 0)
            {
                coada.push(std::make_pair(yy, xx));
                pathMatrix[yy][xx] = pathMatrix[y][x] + 1;
            }
        }

        coada.pop();
    }

    path.resize(0);
    indexInPath = 0;
    reconstructPath((int) game::PacMan::getActualPosition().y, (int) game::PacMan::getActualPosition().x);
}

void game::BlinkyGhost::reconstructPath(int i, int j)
{
    int dl[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    if(pathMatrix[i][j] == 1)
        path.push_back(std::make_pair(i, j));
    else
    {
        int p = -1;
        for(int k = 0; k < 4 && p == -1; k ++)
            if(pathMatrix[i][j] == pathMatrix[i + dl[k]][j + dc[k]] + 1)
                p = k;

        reconstructPath(i + dl[p], j + dc[p]);
        path.push_back(std::make_pair(i, j));
    }
}


