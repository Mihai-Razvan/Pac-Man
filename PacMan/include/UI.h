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
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    sf::Clock gameOverClock;
    static sf::Clock endClock;

    static bool shouldRestart;
    void restartRound();   //when pacman loses a life this method repositions it and the ghosts back to theirs spawn point

    void drawGameStage(sf::RenderWindow&);
    void drawMenuStage(sf::RenderWindow&);
    void drawScoreStage(sf::RenderWindow&);
    void handleGameEvents(sf::Event&, sf::RenderWindow&);
    void handleMenuEvents(sf::Event&, sf::RenderWindow&);
    void handleScoreEvents(sf::Event&, sf::RenderWindow&);
    void drawScore(sf::RenderWindow&, int, int, float);
    void startMatch();
    void gameEnding();

public:

    UI();
    void renderGame();
    void openUISprites();   //to open different UI elements that don t have a class attributed such as lives, score
    void drawUI(sf::RenderWindow&);
    static void setRestart(bool restart);
    static void restartEndClock();
};
}

#endif // UI_H
