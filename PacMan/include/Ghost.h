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
    static sf::Texture frigthenedTextures[2];
    static sf::Sprite frigthenedSprites[2];
    sf::Sprite actualGhost;
    int actualGhostSpriteIndex;
    std::string actualGhostSpriteType;   //chase or frightened; used for clipping when coming back to normal
 //   char direction;    //could pe 'W', 'A', 'S', 'D'
    static float speed;      //per second
    sf::Clock movementClock;
    sf::Clock spriteChangeClock;
    static sf::Clock frightenedClock;
    float spriteChangeInterval;
    int pathMatrix[31][28];
    std::vector<std::pair<int, int>> path;
    int indexInPath;
    static std::string mode;
    static int frigthenedTime;       //how long ghosts stay frightened
    static float timeInFrigthened;    //since ghosts became frightened
    sf::Vector2f spawnPoint;
    static sf::Vector2f respawnPoint;

    virtual void loadSprites() = 0;
    virtual void setInitialGhost() = 0;
    virtual void changeDirection() = 0;
    virtual void changeSprite();

    sf::Vector2f getActualPosition();
    void setGhostOrigin();
    void rotateSprite(float);
    void checkCollision();

    virtual sf::Vector2f findTargetPoint() = 0;
    void makePathMatrix();
    void findPath(sf::Vector2f);
    void reconstructPath(int ,int);
    sf::Vector2f findFrightenedTargetPoint();

public:
    Ghost();
    static void startFrightened();
    static std::string getMode();

    virtual void movement() = 0;
    virtual sf::Sprite& getActualGhost() = 0;

    void restartMovementClock();
};
}

#endif // GHOST_H
