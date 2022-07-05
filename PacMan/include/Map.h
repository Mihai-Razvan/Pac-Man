#ifndef MAP_H
#define MAP_H
#include <string>
#include <SFML/Graphics.hpp>

namespace game
{
class Map
{
private:
    static std::string tileMap[31][28];

    sf::Texture mapTexture;
    sf::Sprite mapSprite;

    sf::RectangleShape rectangles[31][28];

    void makeMapSprite();   //for testing purposes

public:
    Map();
    static std::string getTileMapElement(int, int);
    sf::Sprite& getMapSprite();

    void drawRectangles(sf::RenderWindow&);   //for testing purposes
};
}

#endif // MAP_H
