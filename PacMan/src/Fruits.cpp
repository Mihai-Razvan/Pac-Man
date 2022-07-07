#include "Fruits.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Map.h"
#include "GlobalManager.h"

game::Fruits::Fruits()
{
    loadSprites();
    makeFruitsMap();
}

void game::Fruits::loadSprites()
{
    orangeTexture.loadFromFile("Sprites//fruits//orange.png");

    orangeSprite.setTexture(orangeTexture);

    orangeSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    orangeSprite.setOrigin(orangeTexture.getSize().x / 2, orangeTexture.getSize().y / 2);
}

void game::Fruits::makeFruitsMap()
{
    srand(time(NULL));

    int tileRows = game::GlobalManager::getTileRows();
    int tileCols = game::GlobalManager::getTileCols();

    for(int i = 0; i < tileRows; i++)
        for(int j = 0; j < tileCols; j++)
            fruitsMap[i][j] = "N";

    for(int i = 1; i <= tileRows; i++)
        for(int j = 1; j <= tileCols; j++)
            if(game::Map::getTileMapElement(i, j) == "O" && fruitsMap[i - 1][j] == "N" && fruitsMap[i + 1][j] == "N" && fruitsMap[i][j - 1] == "N" && fruitsMap[i][j + 1] == "N"
                    && fruitsMap[i - 1][j - 1] == "N" && fruitsMap[i - 1][j + 1] == "N" && fruitsMap[i + 1][j - 1] == "N" && fruitsMap[i + 1][j + 1] == "N")
            {
                int randVal = rand() % 4 + 1;

                switch(randVal)
                {
                case(1):
                    fruitsMap[i][j] = "O";  //orange
                    break;
                default:
                    fruitsMap[i][j] = "N";   //none
                    break;
                }
            }
}

void game::Fruits::drawFruits(sf::RenderWindow &window)
{
    int tileRows = game::GlobalManager::getTileRows();
    int tileCols = game::GlobalManager::getTileCols();

    for(int i = 0; i < tileRows; i++)
        for(int j = 0; j < tileCols; j++)
            if(fruitsMap[i][j] == "O")
            {
                float posX = game::GlobalManager::getMapPos().x + j * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
                float posY = game::GlobalManager::getMapPos().y + i * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;

                orangeSprite.setPosition(sf::Vector2f(posX, posY));
                window.draw(orangeSprite);
            }
}

std::string game::Fruits::getFruit(int i, int j)
{
    return fruitsMap[i][j];
}
