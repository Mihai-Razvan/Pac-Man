#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "PacMan.h"
#include "Ghost.h"
#include "BlinkyGhost.h"
#include "Fruits.h"

namespace game
{
class UI
{
private:
    Map gameMap;
    PacMan pacMan;
    BlinkyGhost blinkyGhost;
    Fruits fruits;

    void handleEvents(sf::Event&, sf::RenderWindow&);

public:

    UI();
    void renderGame();

};
}

#endif // UI_H
