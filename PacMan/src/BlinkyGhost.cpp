#include "BlinkyGhost.h"
#include <SFML/Graphics.hpp>
#include "PacMan.h"
#include "GlobalManager.h"
#include "Map.h"
#include "Ghost.h"

game::BlinkyGhost::BlinkyGhost()
{
    loadSprites();
    actualGhost = ghostSprites[0];
    setInitialGhost();

    speed = 150;
    direction = 'D';
    spriteChangeInterval = 0.1f;
    actualGhostSpriteIndex = 0;
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
    float elapsedTime = movementClock.getElapsedTime().asSeconds();
    movementClock.restart();
    float posX, posY;

    if(direction == 'W')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(game::Map::getTileMapElement(actualTile.y - 1, actualTile.x) == "W" && actualGhost.getPosition().y <= limitY)
            return;

        posX = actualGhost.getPosition().x;
        posY = actualGhost.getPosition().y - speed * elapsedTime;
    }
    else if(direction == 'S')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(game::Map::getTileMapElement(actualTile.y + 1, actualTile.x) == "W" && actualGhost.getPosition().y >= limitY)
            return;

        posX = actualGhost.getPosition().x;
        posY = actualGhost.getPosition().y + speed * elapsedTime;
    }
    else if(direction == 'A')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(game::Map::getTileMapElement(actualTile.y, actualTile.x - 1) == "W" && actualGhost.getPosition().x <= limitX)
            return;

        posX = actualGhost.getPosition().x - speed * elapsedTime;
        posY = actualGhost.getPosition().y;
    }
    else if(direction == 'D')
    {
        sf::Vector2f actualTile = getActualPosition();
        float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
        if(game::Map::getTileMapElement(actualTile.y, actualTile.x + 1) == "W" && actualGhost.getPosition().x >= limitX)
            return;

        posX = actualGhost.getPosition().x + speed * elapsedTime;
        posY = actualGhost.getPosition().y;
    }

    float spriteChangeElapsedTime = spriteChangeClock.getElapsedTime().asSeconds();
    if(spriteChangeElapsedTime >= spriteChangeInterval)
    {
        spriteChangeClock.restart();
        if(actualGhostSpriteIndex == 0)
            actualGhostSpriteIndex = 1;
        else
            actualGhostSpriteIndex = 0;

        actualGhost = ghostSprites[actualGhostSpriteIndex];
    }

    setGhostOrigin();
    actualGhost.setPosition(sf::Vector2f(posX, posY));
}

sf::Sprite& game::BlinkyGhost::getActualGhost()
{
    return actualGhost;
}



