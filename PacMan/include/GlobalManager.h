#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include <SFML/Graphics.hpp>

namespace game {

class GlobalManager
{
private:
    static float screenWidth;
    static float screenHeight;
    static int tileRows;
    static int tileCols;
    static int tileSize;    //in pixels

    static sf::Vector2f mapPos;
    static sf::Vector2f mapSize;

public:
    static float getScreenWidth();
    static float getScreenHeight();
    static int getTileRows();
    static int getTileCols();
    static int getTileSize();
    static sf::Vector2f getMapPos();
    static sf::Vector2f getMapSize();

    static void setMapPos(sf::Vector2f mapPos);
    static void setMapSize(sf::Vector2f mapSize);
};
}

#endif // GLOBALMANAGER_H
