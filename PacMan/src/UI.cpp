#include "UI.h"
#include <SFML/Graphics.hpp>
#include "Map.h"

#define TILEROWS 31
#define TILECOLS 28
#define TILESIZE 16

game::UI::UI()
{
    makeRectangles();
}

void game::UI::renderGame()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture texture;
    texture.loadFromFile("D://Projects//CodeBlocks-Projects//PacMan_GitRep//Sprites//map//map.png");
    sf::Sprite mapSprite(texture);
    mapSprite.setPosition(sf::Vector2f(50, 500));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(mapSprite);
        int i, j;
        for(i = 0; i < TILEROWS; i++)
            for(j = 0; j < TILECOLS; j++)
                window.draw(rectangles[i][j]);

        window.display();
    }
}

void game::UI::makeRectangles()
{
    int i, j;
    for(i = 0; i < TILEROWS; i++)
        for(j = 0; j < TILECOLS; j++)
        {
            rectangles[i][j].setSize(sf::Vector2f(TILESIZE, TILESIZE));
            rectangles[i][j].setPosition(sf::Vector2f(j * TILESIZE + 50, i * TILESIZE + 0));
            if(gameMap.getTileMapElement(i, j) == "W")
                rectangles[i][j].setFillColor(sf::Color::Blue);
            else if(gameMap.getTileMapElement(i, j) == "O")
                rectangles[i][j].setFillColor(sf::Color::Black);
            else if(gameMap.getTileMapElement(i, j) == "N")
                rectangles[i][j].setFillColor(sf::Color::Black);
            else if(gameMap.getTileMapElement(i, j) == "G")
                rectangles[i][j].setFillColor(sf::Color::Magenta);
        }
}


