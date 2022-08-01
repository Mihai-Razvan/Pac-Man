#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>

namespace game
{
class Menu
{
private:
    sf::Texture playTexture;
    sf::Sprite playSprite;
    sf::Texture quitTexture;
    sf::Sprite quitSprite;
    std::string selectedButton = "Play";

    void loadSprites();

public:
    Menu();

    sf::Sprite getPlaySprite();
    sf::Sprite getQuitSprite();
    std::string getSelectedButton();
    void setSelectedButton(std::string);
};
}
#endif // MENU_H
