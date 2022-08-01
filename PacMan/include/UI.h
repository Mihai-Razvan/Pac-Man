#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "PacMan.h"
#include "Ghost.h"
#include "BlinkyGhost.h"
#include "Fruits.h"
#include "PinkyGhost.h"
#include "Menu.h"

namespace game
{
class UI
{
private:
    Map gameMap;
    PacMan pacMan;
    BlinkyGhost blinkyGhost;
    PinkyGhost pinkyGhost;
    Fruits fruits;
    Menu menu;

    sf::Texture lifeTexture;
    sf::Sprite lifeSprite;
    sf::Texture digitsTextures[10];
    sf::Sprite digitsSprites[10];

    static bool shouldRestart;
    void restartRound();   //when pacman loses a life this method repositions it and the ghosts back to theirs spawn point

    void handleGameEvents(sf::Event&, sf::RenderWindow&);
    void handleMenuEvents(sf::Event&, sf::RenderWindow&);
    void drawScore(sf::RenderWindow&);

public:

    UI();
    void renderGame();
    void openUISprites();   //to open different UI elements that don t have a class attributed such as lives, score
    void drawUI(sf::RenderWindow&);
    static void setRestart(bool restart);
    void drawGameStage(sf::RenderWindow&);
    void drawMenuStage(sf::RenderWindow&);
};
}

#endif // UI_H
