#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "UI.h"
#include "GlobalManager.h"

float game::GlobalManager::screenWidth = 600.f;
float game::GlobalManager::screenHeight = 600.f;
int game::GlobalManager::tileRows = 31;
int game::GlobalManager::tileCols = 28;
int game::GlobalManager::tileSize = 16;
sf::Vector2f game::GlobalManager::mapPos;
sf::Vector2f game::GlobalManager::mapSize;
sf::Sprite game::PacMan::actualPacMan;
std::string game::Fruits::fruitsMap[31][28];
std::string game::Map::tileMap[31][28] =
{
        {"W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"},
        {"W","O","O","O","O","O","O","O","O","O","O","O","O","W","W","O","O","O","O","O","O","O","O","O","O","O","O","W"},
        {"W","O","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","O","W"},
        {"W","O","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","O","W"},
        {"W","O","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","O","W"},
        {"W","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","W"},
        {"W","O","W","W","W","W","O","W","W","O","W","W","W","W","W","W","W","W","O","W","W","O","W","W","W","W","O","W"},
        {"W","O","W","W","W","W","O","W","W","O","W","W","W","W","W","W","W","W","O","W","W","O","W","W","W","W","O","W"},
        {"W","O","O","O","O","O","O","W","W","O","O","O","O","W","W","O","O","O","O","W","W","O","O","O","O","O","O","W"},
        {"W","W","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","W","W"},
        {"N","N","N","N","N","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","O","O","O","O","O","O","O","O","O","O","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","O","W","W","W","G","G","W","W","W","O","W","W","O","W","N","N","N","N","N"},
        {"W","W","W","W","W","W","O","W","W","O","W","O","O","O","O","O","O","W","O","W","W","O","W","W","W","W","W","W"},
        {"P","O","O","O","O","O","O","O","O","O","W","O","O","O","O","O","O","W","O","O","O","O","O","O","O","O","O","P"},
        {"W","W","W","W","W","W","O","W","W","O","W","O","O","O","O","O","O","W","O","W","W","O","W","W","W","W","W","W"},
        {"N","N","N","N","N","W","O","W","W","O","W","W","W","W","W","W","W","W","O","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","O","O","O","O","O","O","O","O","O","O","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","O","W","W","W","W","W","W","W","W","O","W","W","O","W","N","N","N","N","N"},
        {"W","W","W","W","W","W","O","W","W","O","W","W","W","W","W","W","W","W","O","W","W","O","W","W","W","W","W","W"},
        {"W","O","O","O","O","O","O","O","O","O","O","O","O","W","W","O","O","O","O","O","O","O","O","O","O","O","O","W"},
        {"W","O","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","O","W"},
        {"W","O","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","O","W"},
        {"W","O","O","O","W","W","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","W","W","O","O","O","W"},
        {"W","W","W","O","W","W","O","W","W","O","W","W","W","W","W","W","W","W","O","W","W","O","W","W","O","W","W","W"},
        {"W","W","W","O","W","W","O","W","W","O","W","W","W","W","W","W","W","W","O","W","W","O","W","W","O","W","W","W"},
        {"W","O","O","O","O","O","O","W","W","O","O","O","O","W","W","O","O","O","O","W","W","O","O","O","O","O","O","W"},
        {"W","O","W","W","W","W","W","W","W","W","W","W","O","W","W","O","W","W","W","W","W","W","W","W","W","W","O","W"},
        {"W","O","W","W","W","W","W","W","W","W","W","W","O","W","W","O","W","W","W","W","W","W","W","W","W","W","O","W"},
        {"W","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","W"},
        {"W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W","W"}
};


int main()
{
    game::UI UI;
    UI.renderGame();

    return 0;
}
