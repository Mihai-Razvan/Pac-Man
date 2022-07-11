#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ghost.h"
#include "GlobalManager.h"
#include "PacMan.h"

game::Ghost::Ghost()
{
    frigthenedTextures[0].loadFromFile("Sprites//ghosts//f-0.png");
    frigthenedTextures[1].loadFromFile("Sprites//ghosts//f-1.png");

    frigthenedSprites[0].setTexture(frigthenedTextures[0]);
    frigthenedSprites[1].setTexture(frigthenedTextures[1]);
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
        std::cout << "GAME OVER";
}

void game::Ghost::setMode(std::string mode)
{
    game::Ghost::mode = mode;
}

std::string game::Ghost::getMode()
{
    return mode;
}

void game::Ghost::enterFrightenedMode()
{

}
