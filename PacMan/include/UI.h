#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "PacMan.h"

namespace game
{
class UI
{
private:
    Map gameMap;
    PacMan pacMan;

public:

    UI();
    void renderGame();
};
}

#endif // UI_H
