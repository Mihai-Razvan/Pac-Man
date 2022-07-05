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
        {"W","W","W","W","W","W","O","W","W","W","W","W","N","W","W","N","W","W","W","W","W","O","W","W","W","W","W","W"},
        {"N","N","N","N","N","W","O","W","W","W","W","W","N","W","W","N","W","W","W","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","N","N","N","N","N","N","N","N","N","N","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","N","W","W","W","G","G","W","W","W","N","W","W","O","W","N","N","N","N","N"},
        {"W","W","W","W","W","W","O","W","W","N","W","N","N","N","N","N","N","W","N","W","W","O","W","W","W","W","W","W"},
        {"P","N","N","N","N","N","O","N","N","N","W","N","N","N","N","N","N","W","N","N","N","O","N","N","N","N","N","P"},
        {"W","W","W","W","W","W","O","W","W","N","W","N","N","N","N","N","W","W","N","W","W","O","W","W","W","W","W","W"},
        {"N","N","N","N","N","W","O","W","W","N","W","W","W","W","W","W","W","W","N","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","N","N","N","N","N","N","N","N","N","N","W","W","O","W","N","N","N","N","N"},
        {"N","N","N","N","N","W","O","W","W","N","W","W","W","W","W","W","W","W","N","W","W","O","W","N","N","N","N","N"},
        {"W","W","W","W","W","W","O","W","W","N","W","W","W","W","W","W","W","W","N","W","W","O","W","W","W","W","W","W"},
        {"W","O","O","O","O","O","O","O","O","O","O","O","O","W","W","O","O","O","O","O","O","O","O","O","O","O","O","W"},
        {"W","O","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","O","W"},
        {"W","O","W","W","W","W","O","W","W","W","W","W","O","W","W","O","W","W","W","W","W","O","W","W","W","W","O","W"},
        {"W","O","O","O","W","W","O","O","O","O","O","O","O","N","N","O","O","O","O","O","O","O","W","W","O","O","O","W"},
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
