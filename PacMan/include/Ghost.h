#ifndef GHOST_H
#define GHOST_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ghost.h"
#include "GlobalManager.h"

namespace game
{

class Ghost
{
protected:
    sf::Texture ghostTextures[2];
    sf::Sprite ghostSprites[2];
    sf::Sprite actualGhost;
    int actualGhostSpriteIndex;
    char direction;    //could pe 'W', 'A', 'S', 'D'
    float speed;      //per second
    sf::Clock movementClock;
    sf::Clock spriteChangeClock;
    float spriteChangeInterval;
    int pathMatrix[31][28];
    std::vector<std::pair<int, int>> path;
    int indexInPath;

    virtual void loadSprites() = 0;
    virtual void setInitialGhost() = 0;
    virtual void findPath() = 0;
    virtual void changeDirection() = 0;

    sf::Vector2f getActualPosition();
    void setGhostOrigin();
    void rotateSprite(float);
    void checkCollision();

public:
    Ghost();

    virtual void movement() = 0;
    virtual sf::Sprite& getActualGhost() = 0;
};
}

#endif // GHOST_H
