#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI.h"
#include "Map.h"
#include "GlobalManager.h"
#include "PacMan.h"
#include "Ghost.h"
#include "BlinkyGhost.h"
#include "Fruits.h"
#include "PinkyGhost.h"

game::UI::UI()
{
    openUISprites();
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
            handleEvents(event, window);
        }

        window.clear();
        window.draw(gameMap.getMapSprite());

        fruits.drawFruits(window);

        blinkyGhost.movement();
        window.draw(blinkyGhost.getActualGhost());

         pinkyGhost.movement();
         window.draw(pinkyGhost.getActualGhost());

        pacMan.movement();

        if(shouldRestart == true)       //we should keep it here otherwise exception
            restartRound();

        pacMan.eatFruit();
        window.draw(pacMan.getActualPacMan());

        drawUI(window);

        // gameMap.drawRectangles(window);
        window.display();
    }
}

void game::UI::handleEvents(sf::Event &event, sf::RenderWindow& window)
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
            pacMan.setDirection('D');
            break;
        default:
            break;
        }

    }
}

void game::UI::openUISprites()
{
    lifeTexture.loadFromFile("Sprites//fruits//apple.png");     //to be changes
    lifeSprite.setTexture(lifeTexture);
    lifeSprite.setOrigin(lifeTexture.getSize().x / 2, lifeTexture.getSize().y / 2);
}

void game::UI::drawUI(sf::RenderWindow &window)
{
    for(int i = 0; i < game::GlobalManager::getLives(); i++)
    {
        float posX = 30 + i * 50;
        float posY = game::GlobalManager::getScreenHeight() - 25;
        lifeSprite.setPosition(sf::Vector2f(posX, posY));
        window.draw(lifeSprite);
    }
}

void game::UI::setRestart(bool restart)
{
    shouldRestart = restart;
}

void game::UI::restartRound()
{
    shouldRestart = false;
    pacMan.setDying(false);
    pacMan.toSpawnPoint();
    blinkyGhost.toSpawnPoint();
    pinkyGhost.toSpawnPoint();
}


