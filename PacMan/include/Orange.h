#ifndef ORANGE_H
#define ORANGE_H
#include <SFML/Graphics.hpp>
#include "Fruits.h"

namespace game{

class Orange: public Fruits
{
private:

    void loadSprites();

public:
    Orange();
};
}

#endif // ORANGE_H
