#ifndef PACMAN_H
#define PACMAN_H
#include <SFML/Graphics.hpp>

namespace game{

class PacMan
{
private:
    sf::Texture pacManTextures[11];
    sf::Sprite pacManSprites[11];
    static sf::Sprite actualPacMan;     //the actual sprite of the pacman
    static int actualPacManSpriteIndex;
    static char direction;    //could pe 'W', 'A', 'S', 'D'
    float speed;      //per second
    sf::Clock movementClock;
    sf::Clock spriteChangeClock;
    float spriteChangeInterval;
    static sf::Vector2f spawnPoint;
    static bool dying;   //when it is done the dying animation

    void loadSprites();
    void setInitialPacMan();
    void changeSprite(int);
    static void rotateSprite(float);
    void setPacManOrigin();

public:
    PacMan();

    static sf::Sprite& getActualPacMan();
    void movement();
    void setDirection(char direction);
    static sf::Vector2f getActualPosition();     //returns the tile where pacMan is now positioned
    void eatFruit();
    static void toSpawnPoint();
    static void setDying(bool);
    static bool getDying();
    static int getActualPacManSpriteIndex();
};
}

#endif // PACMAN_H
