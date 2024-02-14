// DemoSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "common.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "My window");

	sf::Sprite chien = LoadSprite("monstre.png", false);
	

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }


        window.clear(sf::Color::Green); 

		BlitSprite(chien, sf::Vector2f(400, 300), 23, window);

        window.display();            
    }


}
