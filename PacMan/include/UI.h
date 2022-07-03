#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include "Map.h"

namespace game
{
class UI
{
private:
    Map gameMap;
    sf::RectangleShape rectangles[31][28];

public:

    UI();
    void renderGame();
    void makeRectangles();
};
}

#endif // UI_H
