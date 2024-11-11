#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Crosshair en el Centro");

    sf::Texture crosshairTexture;
    if (!crosshairTexture.loadFromFile("C:/Mavi/Unidad4_Assets/crosshair.png")) {
        std::cerr << "Error al cargar la imagen del crosshair" << std::endl;
        return -1; 
    }

    sf::Sprite crosshairSprite;
    crosshairSprite.setTexture(crosshairTexture);

    sf::FloatRect bounds = crosshairSprite.getLocalBounds();

    crosshairSprite.setPosition(
        (WINDOW_WIDTH - bounds.width) / 2,
        (WINDOW_HEIGHT - bounds.height) / 2
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw(crosshairSprite);

        window.display();
    }
    return 0;
}
