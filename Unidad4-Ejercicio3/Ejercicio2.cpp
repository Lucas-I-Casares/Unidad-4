#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct Circle {
    sf::Sprite sprite;
    sf::Vector2f position;
};

int main() {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ejercicio 3");

    sf::Texture redCircleTexture;
    if (!redCircleTexture.loadFromFile("C:/Mavi/Unidad4_Assets/rcircle.png")) {
        std::cerr << "Error al cargar la imagen del círculo rojo" << std::endl;
        return -1;
    }

    sf::Texture blueCircleTexture;
    if (!blueCircleTexture.loadFromFile("C:/Mavi/Unidad4_Assets/rcircleb.png")) {
        std::cerr << "Error al cargar la imagen del círculo azul" << std::endl;
        return -1;
    }

    std::vector<Circle> circles;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Circle newCircle;
                    newCircle.sprite.setTexture(redCircleTexture);
                    newCircle.position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    newCircle.sprite.setPosition(newCircle.position);
                    circles.push_back(newCircle);
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    Circle newCircle;
                    newCircle.sprite.setTexture(blueCircleTexture);
                    newCircle.position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    newCircle.sprite.setPosition(newCircle.position);
                    circles.push_back(newCircle);
                }
            }
        }

        window.clear(sf::Color::White);

        for (const auto& circle : circles) {
            window.draw(circle.sprite);
        }

        window.display();
    }

    return 0;
}
