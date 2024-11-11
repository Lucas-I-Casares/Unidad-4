#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const int INITIAL_WIDTH = 800;
    const int INITIAL_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(INITIAL_WIDTH, INITIAL_HEIGHT), "Cambiar Tamaño de la Ventana");

    const int MIN_WIDTH = 100;
    const int MIN_HEIGHT = 100;
    const int MAX_WIDTH = 1000;
    const int MAX_HEIGHT = 1000;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                int newWidth = event.size.width;
                int newHeight = event.size.height;

                if (newWidth < MIN_WIDTH) newWidth = MIN_WIDTH;
                if (newHeight < MIN_HEIGHT) newHeight = MIN_HEIGHT;
                if (newWidth > MAX_WIDTH) newWidth = MAX_WIDTH;
                if (newHeight > MAX_HEIGHT) newHeight = MAX_HEIGHT;

                window.setSize(sf::Vector2u(newWidth, newHeight));
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}
