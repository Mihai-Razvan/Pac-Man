#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GlobalManager.h"
#include "Map.h"

game::Map::Map()
{
    makeMapSprite();
}

void game::Map::makeMapSprite()
{
    if(!mapTexture.loadFromFile("Sprites//map//map.png"))
        std::cout << "Couldn't open game map texture!" << '\n';

    mapSprite.setTexture(mapTexture);

    float sizeX = mapTexture.getSize().x;
    float sizeY = mapTexture.getSize().y;
    float posX = (game::GlobalManager::getScreenWidth() - sizeX) / 2;
    float posY = (game::GlobalManager::getScreenHeight() - sizeY) / 2;
    mapSprite.setPosition(sf::Vector2f(posX, posY));

    game::GlobalManager::setMapPos(sf::Vector2f(posX, posY));
    game::GlobalManager::setMapSize(sf::Vector2f(sizeX, sizeY));
}

sf::Sprite& game::Map::getMapSprite()
{
    return mapSprite;
}

std::string game::Map::getTileMapElement(int i, int j)
{;
    return tileMap[i][j];
}








void game::Map::drawRectangles(sf::RenderWindow &window)
{
    int i, j;
    float initialX = (game::GlobalManager::getScreenWidth() - mapTexture.getSize().x) / 2;
    float initialY = (game::GlobalManager::getScreenHeight() - mapTexture.getSize().y) / 2;

    for(i = 0; i < game::GlobalManager::getTileRows(); i++)
        for(j = 0; j < game::GlobalManager::getTileCols(); j++)
        {
            rectangles[i][j].setSize(sf::Vector2f(game::GlobalManager::getTileSize(), game::GlobalManager::getTileSize()));
            rectangles[i][j].setPosition(sf::Vector2f(j * game::GlobalManager::getTileSize() + initialX, i * game::GlobalManager::getTileSize() + initialY));
            if(tileMap[i][j] == "W")
                rectangles[i][j].setFillColor(sf::Color(3, 65, 252, 128));
            else if(tileMap[i][j] == "O")
                rectangles[i][j].setFillColor(sf::Color(0, 0, 0, 128));
            else if(tileMap[i][j] == "N")
                rectangles[i][j].setFillColor(sf::Color(0, 0, 0, 128));
            else if(tileMap[i][j] == "G")
                rectangles[i][j].setFillColor(sf::Color(233, 237, 7, 128));

            window.draw(rectangles[i][j]);
        }

}

