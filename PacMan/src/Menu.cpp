#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "GlobalManager.h"

game::Menu::Menu()
{
    loadSprites();
}

void game::Menu::loadSprites()
{
    playTexture.loadFromFile("D://Projects//CodeBlocks-Projects//PacMan_GitRep//Sprites//menu//Large_Buttons//Colored_Large_Buttons//Play_Button.png");
    playSprite.setTexture(playTexture);
    playSprite.setScale(sf::Vector2f(0.5f, 0.5f));
    playSprite.setOrigin(sf::Vector2f(playTexture.getSize().x / 2, playTexture.getSize().y / 2));
    playSprite.setPosition(sf::Vector2f(game::GlobalManager::getScreenWidth() / 2, game::GlobalManager::getScreenHeight() / 2 - 100));

    quitTexture.loadFromFile("D://Projects//CodeBlocks-Projects//PacMan_GitRep//Sprites//menu//Large_Buttons//Colored_Large_Buttons//Quit_Button.png");
    quitSprite.setTexture(quitTexture);
    quitSprite.setScale(sf::Vector2f(0.5f, 0.5f));
    quitSprite.setOrigin(sf::Vector2f(quitTexture.getSize().x / 2, quitTexture.getSize().y / 2));
    quitSprite.setPosition(sf::Vector2f(game::GlobalManager::getScreenWidth() / 2, game::GlobalManager::getScreenHeight() / 2 + 100));

    playSprite.setColor(sf::Color::Green);
}

sf::Sprite game::Menu::getPlaySprite()
{
    return playSprite;
}

sf::Sprite game::Menu::getQuitSprite()
{
    return quitSprite;
}

std::string game::Menu::getSelectedButton()
{
    return selectedButton;
}

void game::Menu::setSelectedButton(std::string value)
{
    selectedButton = value;
    if(selectedButton == "Play")
    {
        playSprite.setColor(sf::Color::Green);
        quitSprite.setColor(sf::Color::White);
    }
    else
    {
        quitSprite.setColor(sf::Color::Green);
        playSprite.setColor(sf::Color::White);
    }
}
