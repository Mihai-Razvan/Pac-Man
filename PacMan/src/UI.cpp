#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "UI.h"
#include "Map.h"
#include "GlobalManager.h"
#include "PacMan.h"
#include "Ghost.h"
#include "BlinkyGhost.h"
#include "Fruits.h"
#include "PinkyGhost.h"
#include "Menu.h"

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
            if(game::GlobalManager::getScene() == "Game")
                handleGameEvents(event, window);
            else
                handleMenuEvents(event, window);
        }

        window.clear();

        if(game::GlobalManager::getScene() == "Game")
            drawGameStage(window);
        else
            drawMenuStage(window);

        window.display();
    }
}

void game::UI::drawGameStage(sf::RenderWindow& window)
{
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

    if(game::GlobalManager::getGameStage() == "Ending")
    {
        if(gameOverClock.getElapsedTime().asSeconds() >= 0.3f && gameOverClock.getElapsedTime().asSeconds() <= 0.6f)
            window.draw(gameOverSprite);
        else if(gameOverClock.getElapsedTime().asSeconds() > 0.6f)
            gameOverClock.restart();

        if(endClock.getElapsedTime().asSeconds() >= 5)
            game::GlobalManager::setScene("Menu");
    }

    drawUI(window);
    drawScore(window);

    // gameMap.drawRectangles(window);
}

void game::UI::drawMenuStage(sf::RenderWindow& window)
{
    window.draw(menu.getPlaySprite());
    window.draw(menu.getQuitSprite());
}

void game::UI::handleMenuEvents(sf::Event &event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::Closed)
        window.close();
    else if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
        case sf::Keyboard::W:
            menu.setSelectedButton("Play");
            break;
        case sf::Keyboard::Up:
            menu.setSelectedButton("Play");
            break;
        case sf::Keyboard::S:
            menu.setSelectedButton("Quit");
            break;
        case sf::Keyboard::Down:
            menu.setSelectedButton("Quit");
            break;
        case sf::Keyboard::Enter:
            if(menu.getSelectedButton() == "Play")
            {
                game::GlobalManager::setScene("Game");
                startMatch();
            }
            else
                window.close();
            break;
        default:
            break;
        }
    }
}

void game::UI::handleGameEvents(sf::Event &event, sf::RenderWindow& window)
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

    digitsTextures[0].loadFromFile("Sprites//ui//0.png");
    digitsTextures[1].loadFromFile("Sprites//ui//1.png");
    digitsTextures[2].loadFromFile("Sprites//ui//2.png");
    digitsTextures[3].loadFromFile("Sprites//ui//3.png");
    digitsTextures[4].loadFromFile("Sprites//ui//4.png");
    digitsTextures[5].loadFromFile("Sprites//ui//5.png");
    digitsTextures[6].loadFromFile("Sprites//ui//6.png");
    digitsTextures[7].loadFromFile("Sprites//ui//7.png");
    digitsTextures[8].loadFromFile("Sprites//ui//8.png");
    digitsTextures[9].loadFromFile("Sprites//ui//9.png");
    gameOverTexture.loadFromFile("Sprites//ui//gameover.png");

    digitsSprites[0].setTexture(digitsTextures[0]);
    digitsSprites[1].setTexture(digitsTextures[1]);
    digitsSprites[2].setTexture(digitsTextures[2]);
    digitsSprites[3].setTexture(digitsTextures[3]);
    digitsSprites[4].setTexture(digitsTextures[4]);
    digitsSprites[5].setTexture(digitsTextures[5]);
    digitsSprites[6].setTexture(digitsTextures[6]);
    digitsSprites[7].setTexture(digitsTextures[7]);
    digitsSprites[8].setTexture(digitsTextures[8]);
    digitsSprites[9].setTexture(digitsTextures[9]);
    gameOverSprite.setTexture(gameOverTexture);

    gameOverSprite.setOrigin(gameOverTexture.getSize().x / 2, gameOverTexture.getSize().y / 2);
    gameOverSprite.setPosition(game::GlobalManager::getScreenWidth() / 2, game::GlobalManager::getScreenHeight() / 2);
    gameOverSprite.setScale(2, 2);
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

void game::UI::drawScore(sf::RenderWindow &window)
{
    int numOfDigits = 0;
    int score = game::GlobalManager::getScore();

    if(score == 0)
        numOfDigits = 1;

    while(score)
    {
        numOfDigits++;
        score /= 10;
    }

    score = game::GlobalManager::getScore();
    int digitPos = 0;

    while(numOfDigits > 0)
    {
        int digit = score / (int) pow(10, numOfDigits - 1) % 10;
        digitsSprites[digit].setPosition(sf::Vector2f(10 + digitPos * 20, 20));
        window.draw(digitsSprites[digit]);
        digitPos++;
        numOfDigits--;
    }
}

void game::UI::startMatch()
{
    pacMan.restartMovementClock();
    pacMan.toSpawnPoint();
    blinkyGhost.restartMovementClock();
    blinkyGhost.toSpawnPoint();
    pinkyGhost.restartMovementClock();
    pinkyGhost.toSpawnPoint();

    fruits.makeFruitsMap();
    game::GlobalManager::setGameStage("Playing");
    game::GlobalManager::setLives(3);
    game::GlobalManager::setScore(0);
    pacMan.setDying(false);
}

void game::UI::restartEndClock()
{
    endClock.restart();
}
