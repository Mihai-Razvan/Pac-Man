#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "UI.h"
#include "GlobalManager.h"
#include "Fruits.h"
#include "PacMan.h"
#include "BlinkyGhost.h"
#include "PinkyGhost.h"

bool game::UI::shouldRestart = false;
sf::Clock game::UI::endClock;

float game::GlobalManager::screenWidth = 600.f;
float game::GlobalManager::screenHeight = 600.f;
int game::GlobalManager::tileRows = 31;
int game::GlobalManager::tileCols = 28;
int game::GlobalManager::tileSize = 16;
int game::GlobalManager::score = 0;
int game::GlobalManager::lives = 3;
sf::Vector2f game::GlobalManager::mapPos;
sf::Vector2f game::GlobalManager::mapSize;
std::string game::GlobalManager::scene = "Menu";
std::string game::GlobalManager::gameStage = "Playing";

sf::Sprite game::PacMan::actualPacMan;
sf::Vector2f game::PacMan::spawnPoint;
bool game::PacMan::dying = false;
int game::PacMan::actualPacManSpriteIndex;
char game::PacMan::direction;

std::string game::Ghost::mode = "Chase";
sf::Texture game::Ghost::frigthenedTextures[2];
sf::Sprite game::Ghost::frigthenedSprites[2];
int game::Ghost::frigthenedTime = 15;
float game::Ghost::timeInFrigthened;
float game::Ghost::speed = 100;
sf::Vector2f game::Ghost::respawnPoint;
sf::Clock game::Ghost::frightenedClock;

char game::BlinkyGhost::direction = 'D';

char game::PinkyGhost::direction = 'A';

std::string game::Fruits::fruitsMap[31][28];
int game::Fruits::orangeScore = 100;
int game::Fruits::strawberryScore = 300;

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


