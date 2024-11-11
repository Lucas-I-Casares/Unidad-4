#include <SFML/Graphics.hpp>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float POINT_RADIUS = 10.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ejercicio 2");
    window.setFramerateLimit(60);

    std::vector<sf::CircleShape> puntos(4);
    puntos[0].setPosition(0, 0); 
    puntos[1].setPosition(WINDOW_WIDTH - 2 * POINT_RADIUS, 0); 
    puntos[2].setPosition(0, WINDOW_HEIGHT - 2 * POINT_RADIUS); 
    puntos[3].setPosition(WINDOW_WIDTH - 2 * POINT_RADIUS, WINDOW_HEIGHT - 2 * POINT_RADIUS);

    for (auto& punto : puntos) {
        punto.setRadius(POINT_RADIUS);
        punto.setFillColor(sf::Color::Red);
    }

    bool isDragging = false;
    int draggedPointIndex = -1;
    sf::Vector2f mouseOffset;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (int i = 0; i < puntos.size(); ++i) {
                    if (puntos[i].getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        draggedPointIndex = i;
                        mouseOffset = puntos[i].getPosition() - mousePos;
                        break;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
                draggedPointIndex = -1;
            }
        }

        if (isDragging && draggedPointIndex != -1) {
            sf::Vector2f newMousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            puntos[draggedPointIndex].setPosition(newMousePos + mouseOffset);
        }

        window.clear(sf::Color::Black);
        for (const auto& punto : puntos) {
            window.draw(punto);
        }
        window.display();
    }

    return 0;
}
