#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include <SFML/Graphics.hpp>
#include <string>

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

    static int score;
    static int lives;
    static std::string scene;
    static std::string gameStage;   // could pe playing or game over

public:
    static float getScreenWidth();
    static float getScreenHeight();
    static int getTileRows();
    static int getTileCols();
    static int getTileSize();
    static sf::Vector2f getMapPos();
    static sf::Vector2f getMapSize();

    static void setMapPos(sf::Vector2f);
    static void setMapSize(sf::Vector2f);

    static void setScore(int);
    static int getScore();
    static void setLives(int);
    static int getLives();
    static void setScene(std::string);
    static std::string getScene();
    static void setGameStage(std::string);
    static std::string getGameStage();
};
}

#endif // GLOBALMANAGER_H
