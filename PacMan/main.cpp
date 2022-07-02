#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define SPEED 500

int randNum()
{
    srand((unsigned) time(0));
    int result = (rand() % 4);
    return result;
}

void setSphere(sf::RenderWindow& window, sf::Clock& clock, sf::CircleShape& shape, std::string& actualDirection, int& lastRand, sf::Color colorArray[])
{
     sf::Time elapsedTime = clock.getElapsedTime();
        clock.restart();

        if(actualDirection == "BR")
        {
            shape.move(SPEED * elapsedTime.asSeconds(), SPEED * elapsedTime.asSeconds());
            if(shape.getPosition().x + 2 * shape.getRadius() >= window.getSize().x && shape.getPosition().y + 2 * shape.getRadius() >= window.getSize().y)
            {
                actualDirection = "TL";

                int randVal = randNum();
                while(randVal == lastRand)
                    randVal = randNum();

                lastRand = randVal;
                shape.setFillColor(colorArray[randVal]);

                std::cout<<"M"<<std::endl;
            }
            else if(shape.getPosition().x + 2* shape.getRadius() >= window.getSize().x)
                actualDirection = "BL";
            else if(shape.getPosition().y + 2 * shape.getRadius() >= window.getSize().y)
                actualDirection = "TR";
        }
        else if(actualDirection == "TR")
        {
            shape.move(SPEED * elapsedTime.asSeconds(), -SPEED * elapsedTime.asSeconds());
            if(shape.getPosition().x + 2 * shape.getRadius() >= window.getSize().x && shape.getPosition().y <= 0)
            {
                actualDirection = "BL";

                int randVal = randNum();
                while(randVal == lastRand)
                    randVal = randNum();

                lastRand = randVal;
                shape.setFillColor(colorArray[randVal]);

                std::cout<<"M"<<std::endl;
            }
            else if(shape.getPosition().x + 2 * shape.getRadius() >= window.getSize().x)
                actualDirection = "TL";
            else if(shape.getPosition().y <= 0)
                actualDirection = "BR";
        }
        else if(actualDirection == "BL")
        {
            shape.move(-SPEED * elapsedTime.asSeconds(), SPEED * elapsedTime.asSeconds());
            if(shape.getPosition().x <= 0 && shape.getPosition().y + 2* shape.getRadius() >= window.getSize().y)
            {
                actualDirection = "TR";

                int randVal = randNum();
                while(randVal == lastRand)
                    randVal = randNum();

                lastRand = randVal;
                shape.setFillColor(colorArray[randVal]);

                std::cout<<"M"<<std::endl;
            }
            else if(shape.getPosition().x <= 0)
                actualDirection = "BR";
            else if(shape.getPosition().y + 2 * shape.getRadius() >= window.getSize().y)
                actualDirection = "TL";
        }
        else if(actualDirection == "TL")
        {
            shape.move(-SPEED * elapsedTime.asSeconds(), -SPEED * elapsedTime.asSeconds());
            if(shape.getPosition().x <= 0 && shape.getPosition().y <= 0)
            {
                actualDirection = "BR";

                int randVal = randNum();
                while(randVal == lastRand)
                    randVal = randNum();

                lastRand = randVal;
                shape.setFillColor(colorArray[randVal]);

                std::cout<<"M"<<std::endl;
            }
            else if(shape.getPosition().x <= 0)
                actualDirection = "TR";
            else if(shape.getPosition().y <= 0)
                actualDirection = "BL";
        }
}

sf::Sprite& makeSprite()
{
    sf::Texture texture;
    texture.loadFromFile("ghost.jpg");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
}


int main()
{
    sf::Color colorArray[4] = {sf::Color::Blue, sf::Color::Magenta, sf::Color::Yellow, sf::Color::White};
    std::string actualDirection = "BR";
    int lastRand = -1;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(window.getSize().x / 2 - shape.getRadius(), window.getSize().y / 2 - shape.getRadius());

    sf::Sprite sprite = makeSprite();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

     //  setSphere(window, clock, shape, actualDirection, lastRand, colorArray);


        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
