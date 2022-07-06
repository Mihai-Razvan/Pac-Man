#ifndef PACMAN_H
#define PACMAN_H
#include <SFML/Graphics.hpp>

namespace game{

class PacMan
{
private:
    sf::Texture pacManTextures[11];
    sf::Sprite pacManSprites[11];
    sf::Sprite actualPacMan;     //the actual sprite of the pacman
    int actualPacManSpriteIndex;
    char direction;    //could pe 'W', 'A', 'S', 'D'
    float speed;      //per second
    sf::Clock movementClock;
    sf::Clock spriteChangeClock;
    float spriteChangeInterval;

    void loadSprites();
    void setInitialPacMan();
    sf::Vector2f getActualPosition();     //returns the tile where pacMan is now positioned
    void changeSprite(int);
    void rotateSprite(float);
    void setPacManOrigin();

public:
    PacMan();

    sf::Sprite& getActualPacMan();
    void movement();
    void setDirection(char direction);
};
}

#endif // PACMAN_H
