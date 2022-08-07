#include <iostream>
#include "PacMan.h"
#include "GlobalManager.h"
#include "Map.h"
#include "Fruits.h"
#include "Ghost.h"
#include "UI.h"

game::PacMan::PacMan()
{
    loadSprites();
    actualPacMan = pacManSprites[0];
    rotateSprite(180);
    setInitialPacMan();

    speed = 150;
    direction = 'D';
    spriteChangeInterval = 0.1f;
    actualPacManSpriteIndex = 0;
}

void game::PacMan::loadSprites()
{
    pacManTextures[0].loadFromFile("Sprites//pacman//0.png");
    pacManTextures[1].loadFromFile("Sprites//pacman//1.png");
    pacManTextures[2].loadFromFile("Sprites//pacman//2.png");
    pacManTextures[3].loadFromFile("Sprites//pacman//d-0.png");
    pacManTextures[4].loadFromFile("Sprites//pacman//d-1.png");
    pacManTextures[5].loadFromFile("Sprites//pacman//d-2.png");
    pacManTextures[6].loadFromFile("Sprites//pacman//d-3.png");
    pacManTextures[7].loadFromFile("Sprites//pacman//d-4.png");
    pacManTextures[8].loadFromFile("Sprites//pacman//d-5.png");
    pacManTextures[9].loadFromFile("Sprites//pacman//d-6.png");
    pacManTextures[10].loadFromFile("Sprites//pacman//d-7.png");

    pacManSprites[0].setTexture(pacManTextures[0]);
    pacManSprites[1].setTexture(pacManTextures[1]);
    pacManSprites[2].setTexture(pacManTextures[2]);
    pacManSprites[3].setTexture(pacManTextures[3]);
    pacManSprites[4].setTexture(pacManTextures[4]);
    pacManSprites[5].setTexture(pacManTextures[5]);
    pacManSprites[6].setTexture(pacManTextures[6]);
    pacManSprites[7].setTexture(pacManTextures[7]);
    pacManSprites[8].setTexture(pacManTextures[8]);
    pacManSprites[9].setTexture(pacManTextures[9]);
    pacManSprites[10].setTexture(pacManTextures[10]);
}

void game::PacMan::setInitialPacMan()
{
    setPacManOrigin();
    float posX = game::GlobalManager::getMapPos().x + game::GlobalManager::getTileSize() * 1.5;
    float posY = game::GlobalManager::getMapPos().y + (game::GlobalManager::getTileRows() / 2 - 1) * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
    spawnPoint = sf::Vector2f(posX, posY);
    actualPacMan.setPosition(spawnPoint);   //pacMan starting position
}

sf::Sprite& game::PacMan::getActualPacMan()
{
    return actualPacMan;
}

void game::PacMan::movement()
{
    float elapsedTime = movementClock.getElapsedTime().asSeconds();
    movementClock.restart();
    float posX = actualPacMan.getPosition().x;
    float posY = actualPacMan.getPosition().y;

    if(dying == false && game::GlobalManager::getScene() == "Game" && game::GlobalManager::getGameStage() == "Playing")
    {
        if(direction == 'W')
        {
            sf::Vector2f actualTile = getActualPosition();
            float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
            //the Y coordinates pacMan can t go further in case there is a wall on the next tile;
            if(game::Map::getTileMapElement(actualTile.y - 1, actualTile.x) == "W" && actualPacMan.getPosition().y <= limitY)
                return;

            posX = actualPacMan.getPosition().x;
            posY = actualPacMan.getPosition().y - speed * elapsedTime;
            rotateSprite(90);
        }
        else if(direction == 'S')
        {
            sf::Vector2f actualTile = getActualPosition();
            float limitY = game::GlobalManager::getMapPos().y + actualTile.y * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
            if(game::Map::getTileMapElement(actualTile.y + 1, actualTile.x) == "W" && actualPacMan.getPosition().y >= limitY)
                return;

            posX = actualPacMan.getPosition().x;
            posY = actualPacMan.getPosition().y + speed * elapsedTime;
            rotateSprite(270);
        }
        else if(direction == 'A')
        {
            sf::Vector2f actualTile = getActualPosition();
            float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
            if(game::Map::getTileMapElement(actualTile.y, actualTile.x - 1) == "W" && actualPacMan.getPosition().x <= limitX)
                return;

            posX = actualPacMan.getPosition().x - speed * elapsedTime;
            posY = actualPacMan.getPosition().y;
            rotateSprite(0);
        }
        else if(direction == 'D')
        {
            sf::Vector2f actualTile = getActualPosition();
            float limitX = game::GlobalManager::getMapPos().x + actualTile.x * game::GlobalManager::getTileSize() + game::GlobalManager::getTileSize() / 2;
            if(game::Map::getTileMapElement(actualTile.y, actualTile.x + 1) == "W" && actualPacMan.getPosition().x >= limitX)
                return;

            posX = actualPacMan.getPosition().x + speed * elapsedTime;
            posY = actualPacMan.getPosition().y;
            rotateSprite(180);
        }

        float spriteChangeElapsedTime = spriteChangeClock.getElapsedTime().asSeconds();
        if(spriteChangeElapsedTime >= spriteChangeInterval)
        {
            spriteChangeClock.restart();
            if(actualPacManSpriteIndex == 2)
                actualPacManSpriteIndex = 0;
            else
                actualPacManSpriteIndex++;

            actualPacMan = pacManSprites[actualPacManSpriteIndex];
        }

        if(game::Map::getTileMapElement(getActualPosition().y, getActualPosition().x) == "P")
            game::GlobalManager::setScene("Score");

    }
    else if(game::GlobalManager::getGameStage() == "Playing")
    {
        float spriteChangeElapsedTime = spriteChangeClock.getElapsedTime().asSeconds();
        if(spriteChangeElapsedTime >= spriteChangeInterval)
        {
            spriteChangeClock.restart();
            if(actualPacManSpriteIndex < 3)
                actualPacManSpriteIndex = 3;
            else
                actualPacManSpriteIndex++;

            if(actualPacManSpriteIndex == 11)
            {
                actualPacManSpriteIndex = 0;
                actualPacMan = pacManSprites[0];
                game::UI::setRestart(true);
                return;
            }

            actualPacMan = pacManSprites[actualPacManSpriteIndex];
        }
    }

    // setPacManOrigin();
    actualPacMan.setPosition(sf::Vector2f(posX, posY));
}

void game::PacMan::setDirection(char direction)
{
    sf::Vector2f actualPosition = getActualPosition();

    if(direction == 'W')
    {
        if(game::Map::getTileMapElement(actualPosition.y - 1, actualPosition.x) == "W")
            return;

        float tileCenterX = game::GlobalManager::getMapPos().x + getActualPosition().x * game::GlobalManager::getTileSize()  + game::GlobalManager::getTileSize() / 2;
        actualPacMan.setPosition(sf::Vector2f(tileCenterX, actualPacMan.getPosition().y));     //so it wont overlap walls visually if player presses key to early or too late
    }

    if(direction == 'S')
    {
        if(game::Map::getTileMapElement(actualPosition.y + 1, actualPosition.x) == "W")
            return;

        float tileCenterX = game::GlobalManager::getMapPos().x + getActualPosition().x * game::GlobalManager::getTileSize()  + game::GlobalManager::getTileSize() / 2;
        actualPacMan.setPosition(sf::Vector2f(tileCenterX, actualPacMan.getPosition().y));
    }

    if(direction == 'A')
    {
        if(game::Map::getTileMapElement(actualPosition.y, actualPosition.x - 1) == "W")
            return;

        float tileCenterY = game::GlobalManager::getMapPos().y + getActualPosition().y * game::GlobalManager::getTileSize()  + game::GlobalManager::getTileSize() / 2;
        actualPacMan.setPosition(sf::Vector2f(actualPacMan.getPosition().x, tileCenterY));
    }

    if(direction == 'D')
    {
        if(game::Map::getTileMapElement(actualPosition.y, actualPosition.x + 1) == "W")
            return;

        float tileCenterY = game::GlobalManager::getMapPos().y + getActualPosition().y * game::GlobalManager::getTileSize()  + game::GlobalManager::getTileSize() / 2;
        actualPacMan.setPosition(sf::Vector2f(actualPacMan.getPosition().x, tileCenterY));
    }

    this->direction = direction;
}

sf::Vector2f game::PacMan::getActualPosition()
{
    int tileColumn = (actualPacMan.getPosition().x - game::GlobalManager::getMapPos().x) / game::GlobalManager::getTileSize();
    int tileRow = (actualPacMan.getPosition().y - game::GlobalManager::getMapPos().y) / game::GlobalManager::getTileSize();

    return sf::Vector2f(tileColumn, tileRow);
}

void game::PacMan::changeSprite(int pos)
{
    actualPacMan = pacManSprites[pos];
}

void game::PacMan::rotateSprite(float angle)
{
    actualPacMan.setRotation(angle);
}

void game::PacMan::setPacManOrigin()
{
    float sizeX = pacManTextures[0].getSize().x;
    float sizeY = pacManTextures[0].getSize().y;
    for(int i = 0; i <= 10; i++)
        pacManSprites[i].setOrigin(sf::Vector2f(sizeX / 2, sizeY / 2));
}

void game::PacMan::eatFruit()
{
    sf::Vector2f actualPosition = getActualPosition();

    actualPosition = getActualPosition();
    if(game::Fruits::getFruit(actualPosition.y, actualPosition.x) == "O")   //orange
    {
        game::Fruits::setFruit(actualPosition.y, actualPosition.x, "N");
        int newScore = game::GlobalManager::getScore() + game::Fruits::getOrangeScore();
        game::GlobalManager::setScore(newScore);
    }
    else if(game::Fruits::getFruit(actualPosition.y, actualPosition.x) == "S")   //strawberry
    {
        game::Fruits::setFruit(actualPosition.y, actualPosition.x, "N");
        int newScore = game::GlobalManager::getScore() + game::Fruits::getStrawberryScore();
        game::GlobalManager::setScore(newScore);

        game::Ghost::startFrightened();
    }

}

void game::PacMan::toSpawnPoint()
{
    actualPacMan.setPosition(spawnPoint);
    rotateSprite(180);
    direction = 'R';
}

void game::PacMan::setDying(bool dying)
{
    game::PacMan::dying = dying;
}

bool game::PacMan::getDying()
{
    return dying;
}

int game::PacMan::getActualPacManSpriteIndex()
{
    return actualPacManSpriteIndex;
}

char game::PacMan::getDirection()
{
    return game::PacMan::direction;
}

void game::PacMan::restartMovementClock()
{
    movementClock.restart();
}
