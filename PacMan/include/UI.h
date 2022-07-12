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
    static PacMan pacMan;
    BlinkyGhost blinkyGhost;
    Fruits fruits;

    sf::Texture lifeTexture;
    sf::Sprite lifeSprite;

    void handleEvents(sf::Event&, sf::RenderWindow&);

public:

    UI();
    void renderGame();
    void openUISprites();   //to open different UI elements that don t have a class attributed such as lives, score
    void drawUI(sf::RenderWindow&);
    static void restartRound();   //when pacman loses a life this method repositions it and the ghosts back to theirs spawn point
};
}

#endif // UI_H
