#ifndef BLINKYGHOST_H
#define BLINKYGHOST_H
#include <SFML/Graphics.hpp>
#include "PacMan.h"
#include "GlobalManager.h"
#include "Map.h"
#include "Ghost.h"

namespace game
{

class BlinkyGhost: public Ghost
{
private:

    static char direction;

    void loadSprites();
    void setInitialGhost();
    void changeDirection();
    sf::Vector2f findTargetPoint();

public:
    BlinkyGhost();

    sf::Sprite& getActualGhost();
    void movement();
    static void toSpawnPoint();
};
}

#endif // BLINKYGHOST_H
