#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mover Cuadrado y Cambiar a Círculo");

    sf::Texture squareTexture;
    if (!squareTexture.loadFromFile("C:/Mavi/Unidad4_Assets/cuad_yellow.png")) {
        std::cerr << "Error al cargar la imagen del cuadrado" << std::endl;
        return -1;
    }

    sf::Texture circleTexture;
    if (!circleTexture.loadFromFile("C:/Mavi/Unidad4_Assets/rcircle.png")) {
        std::cerr << "Error al cargar la imagen del círculo" << std::endl;
        return -1;
    }

    sf::Sprite squareSprite;
    squareSprite.setTexture(squareTexture);

    sf::Sprite circleSprite;
    circleSprite.setTexture(circleTexture);

    squareSprite.setScale(1.0f, 1.0f);
    circleSprite.setScale(2.0f, 2.0f); 

    sf::Sprite currentSprite = squareSprite;

    currentSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    float speed = 5.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    if (currentSprite.getPosition().x > 0)
                        currentSprite.move(-speed, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    if (currentSprite.getPosition().x < WINDOW_WIDTH - currentSprite.getGlobalBounds().width)
                        currentSprite.move(speed, 0);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    if (currentSprite.getPosition().y > 0)
                        currentSprite.move(0, -speed);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    if (currentSprite.getPosition().y < WINDOW_HEIGHT - currentSprite.getGlobalBounds().height)
                        currentSprite.move(0, speed);
                }

                if (event.key.code == sf::Keyboard::Space) {
                    // Cambiar entre cuadrado y círculo
                    if (currentSprite.getTexture() == &squareTexture) {
                        currentSprite.setTexture(circleTexture);
                        currentSprite.setScale(0.5f, 0.5f);  // Asegurarse de que el círculo se mantenga pequeño
                    }
                    else {
                        currentSprite.setTexture(squareTexture);
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(currentSprite);
        window.display();
    }

    return 0;
}
