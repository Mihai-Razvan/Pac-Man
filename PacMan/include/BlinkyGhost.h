#ifndef BLINKYGHOST_H
#define BLINKYGHOST_H
#include <SFML/Graphics.hpp>
#include "PacMan.h"
#include "GlobalManager.h"
#include "Map.h"
#include "Ghost.h"

namespace game{

class BlinkyGhost: public Ghost
{
private:
    void loadSprites();
    void setInitialGhost();


public:
    BlinkyGhost();

    sf::Sprite& getActualGhost();
    void movement();
};
}

#endif // BLINKYGHOST_H
