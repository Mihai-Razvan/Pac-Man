#include <SFML/Graphics.hpp>
#include "GlobalManager.h"
#include <string>

float game::GlobalManager::getScreenWidth()
{
    return screenWidth;
}

float game::GlobalManager::getScreenHeight()
{
    return screenHeight;
}

int game::GlobalManager::getTileRows()
{
    return tileRows;
}

int game::GlobalManager::getTileCols()
{
    return tileCols;
}

int game::GlobalManager::getTileSize()
{
    return tileSize;
}

sf::Vector2f game::GlobalManager::getMapPos()
{
    return mapPos;
}

sf::Vector2f game::GlobalManager::getMapSize()
{
    return mapSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void game::GlobalManager::setMapPos(sf::Vector2f mapPos)
{
    game::GlobalManager::mapPos = mapPos;
}

void game::GlobalManager::setMapSize(sf::Vector2f mapSize)
{
    game::GlobalManager::mapSize = mapSize;
}

int game::GlobalManager::getScore()
{
    return score;
}

void game::GlobalManager::setScore(int score)
{
    game::GlobalManager::score = score;
}

void game::GlobalManager::setLives(int lives)
{
    game::GlobalManager::lives = lives;
}

int game::GlobalManager::getLives()
{
    return lives;
}

void game::GlobalManager::setStage(std::string stage)
{
    game::GlobalManager::stage = stage;
}

std::string game::GlobalManager::getStage()
{
    return game::GlobalManager::stage;
}
