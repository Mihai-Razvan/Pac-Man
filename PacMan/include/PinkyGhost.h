#ifndef PINKYGHOST_H
#define PINKYGHOST_H
#include <SFML/Graphics.hpp>
#include "PacMan.h"
#include "GlobalManager.h"
#include "Map.h"
#include "Ghost.h"

namespace game
{
class PinkyGhost: public Ghost
{
private:

    static char direction;

    void loadSprites();
    void setInitialGhost();
    void changeDirection();
    sf::Vector2f findTargetPoint();

public:
    PinkyGhost();

    sf::Sprite& getActualGhost();
    void movement();
    void toSpawnPoint();
};
}

#endif // PINKYGHOST_H
