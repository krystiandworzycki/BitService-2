#include <iostream>
#include <SFML/Graphics.hpp>

#include "Logger.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "BitService 2", sf::Style::Default);

    Logger::log("Uruchomiono grę!");

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        window.display();
    }

    window.close();

    Logger::log("Zamknięto grę!");

    return 0;
}