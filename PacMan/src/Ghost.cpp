#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "Ghost.h"
#include "GlobalManager.h"
#include "PacMan.h"
#include "Map.h"
#include "UI.h"

game::Ghost::Ghost()
{
    frigthenedTextures[0].loadFromFile("Sprites//ghosts//f-0.png");
    frigthenedTextures[1].loadFromFile("Sprites//ghosts//f-1.png");

    frigthenedSprites[0].setTexture(frigthenedTextures[0]);
    frigthenedSprites[1].setTexture(frigthenedTextures[1]);

    float respawnX = game::GlobalManager::getScreenWidth() / 2;
    float respawnY = game::GlobalManager::getScreenHeight() / 2 - game::GlobalManager::getTileSize();
    respawnPoint = sf::Vector2f(respawnX, respawnY);
}

void game::Ghost::setGhostOrigin()
{
    float sizeX = actualGhost.getTexture()->getSize().x;
    float sizeY = actualGhost.getTexture()->getSize().y;
    actualGhost.setOrigin(sf::Vector2f(sizeX / 2, sizeY / 2));
}

sf::Vector2f game::Ghost::getActualPosition()
{
    int tileColumn = (actualGhost.getPosition().x - game::GlobalManager::getMapPos().x) / game::GlobalManager::getTileSize();
    int tileRow = (actualGhost.getPosition().y - game::GlobalManager::getMapPos().y) / game::GlobalManager::getTileSize();

    return sf::Vector2f(tileColumn, tileRow);
}

void game::Ghost::rotateSprite(float angle)
{
    actualGhost.setRotation(angle);
}

void game::Ghost::checkCollision()
{
    sf::Vector2f ghostPosition = getActualPosition();
    sf::Vector2f pacManPosition = game::PacMan::getActualPosition();

    if(ghostPosition.x == pacManPosition.x && ghostPosition.y == pacManPosition.y)
    {
        if(mode == "Chase")
        {
            int newLives = game::GlobalManager::getLives() - 1;
            game::GlobalManager::setLives(newLives);
            game::UI::restartRound();
            if(newLives == 0)
                std::cout << "GAME OVER" << std::endl;
        }
        else if(mode == "Frightened")
            actualGhost.setPosition(respawnPoint);
    }
}

void game::Ghost::startFrightened()
{
    mode = "Frightened";
    frightenedClock.restart();
}

std::string game::Ghost::getMode()
{
    return mode;
}

void game::Ghost::changeSprite()
{
    if(mode == "Chase")
    {
        if(actualGhostSpriteIndex == 0)
            actualGhostSpriteIndex = 1;
        else
            actualGhostSpriteIndex = 0;

        actualGhost = ghostSprites[actualGhostSpriteIndex];

    }
    else if(mode == "Frightened")
    {
        if(actualGhostSpriteIndex == 0)
            actualGhostSpriteIndex = 1;
        else
            actualGhostSpriteIndex = 0;

        if(frigthenedTime - timeInFrigthened <= 5)   //it starts clipping in the last 5 sec
        {
            if(actualGhostSpriteType == "Chase")
            {
                actualGhostSpriteType = "Frightened";
                actualGhost = frigthenedSprites[actualGhostSpriteIndex];
            }
            else
            {
                actualGhostSpriteType = "Chase";
                actualGhost = ghostSprites[actualGhostSpriteIndex];
            }
        }
        else
              actualGhost = frigthenedSprites[actualGhostSpriteIndex];
    }
}

void game::Ghost::makePathMatrix()  //starts from ghost position
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
}

void game::Ghost::findPath(sf::Vector2f target)
{
    makePathMatrix();
    path.resize(0);
    indexInPath = 0;
    reconstructPath(target.x, target.y);
}

void game::Ghost::reconstructPath(int i, int j)
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

sf::Vector2f game::Ghost::findFrightenedTargetPoint()
{
    sf::Vector2f furtherestPoint;
    int maxDistance = 0;
    int dl[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for(int i = 0; i < 31; i++)
        for(int j = 0; j < 28; j++)
            pathMatrix[i][j] = 0;

    pathMatrix[(int) game::PacMan::getActualPosition().y][(int) game::PacMan::getActualPosition().x] = 1;

    std::queue<std::pair<int, int>> coada;
    coada.push(std::make_pair(game::PacMan::getActualPosition().y, game::PacMan::getActualPosition().x));

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
                if(pathMatrix[yy][xx] > maxDistance)
                {
                    maxDistance = pathMatrix[yy][xx];
                    furtherestPoint = sf::Vector2f(yy, xx);
                }
            }
        }

        coada.pop();
    }

    return furtherestPoint;
}



