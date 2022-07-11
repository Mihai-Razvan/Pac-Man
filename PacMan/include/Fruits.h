#ifndef FRUITS_H
#define FRUITS_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Map.h"

namespace game{

class Fruits
{
private:
    static std::string fruitsMap[31][28];

protected:
    sf::Texture orangeTexture;
    sf::Sprite orangeSprite;
    sf::Texture strawberryTexture;
    sf::Sprite strawberrySprite;

    static int orangeScore;
    static int strawberryScore;

    void loadSprites();

public:
    Fruits();

    void makeFruitsMap();
    void drawFruits(sf::RenderWindow&);
    static std::string getFruit(int, int);
    static void setFruit(int, int, std::string);
    static int getOrangeScore();
    static int getStrawberryScore();
};
}
#endif // FRUITS_H
