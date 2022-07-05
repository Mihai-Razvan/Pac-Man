#include <SFML/Graphics.hpp>
#include "GlobalManager.h"

float game::GlobalManager::getScreenWidth()
{
    return game::GlobalManager::screenWidth;
}

float game::GlobalManager::getScreenHeight()
{
    return game::GlobalManager::screenHeight;
}

int game::GlobalManager::getTileRows()
{
    return game::GlobalManager::tileRows;
}

int game::GlobalManager::getTileCols()
{
    return game::GlobalManager::tileCols;
}

int game::GlobalManager::getTileSize()
{
    return game::GlobalManager::tileSize;
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
