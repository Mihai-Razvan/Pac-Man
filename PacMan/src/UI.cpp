#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI.h"
#include "Map.h"
#include "GlobalManager.h"
#include "PacMan.h"

game::UI::UI()
{

}

void game::UI::renderGame()
{
    sf::RenderWindow window(sf::VideoMode(game::GlobalManager::getScreenWidth(), game::GlobalManager::getScreenHeight()), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::W:
                    pacMan.setDirection('W');
                    break;
                case sf::Keyboard::Up:
                    pacMan.setDirection('W');
                    break;

                case sf::Keyboard::A:
                    pacMan.setDirection('A');
                    break;
                case sf::Keyboard::Left:
                    pacMan.setDirection('A');
                    break;

                case sf::Keyboard::S:
                    pacMan.setDirection('S');
                    break;
                case sf::Keyboard::Down:
                    pacMan.setDirection('S');
                    break;

                case sf::Keyboard::D:
                    pacMan.setDirection('D');
                    break;
                case sf::Keyboard::Right:
                    pacMan.setDirection('Ds');
                    break;
                }

            }
        }

        window.clear();
        window.draw(gameMap.getMapSprite());
        pacMan.movement();
        window.draw(pacMan.getActualPacMan());
        //  gameMap.drawRectangles(window);
        window.display();
    }
}




