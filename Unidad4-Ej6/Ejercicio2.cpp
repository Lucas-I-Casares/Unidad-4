#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Enemy {
public:
    sf::Sprite sprite;
    bool isDefeated;

    Enemy(const sf::Texture& texture) {
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);
        resetPosition();
        isDefeated = false;
    }

    void resetPosition() {
        int x = rand() % 700 + 50; 
        int y = rand() % 500 + 50; 
        sprite.setPosition(sf::Vector2f(x, y));
    }

    void draw(sf::RenderWindow& window) {
        if (!isDefeated) {
            window.draw(sprite);
        }
    }

    void checkCollision(const sf::Vector2i& mousePos) {
        if (sprite.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
            isDefeated = true;
        }
    }
};

class Crosshair {
public:
    sf::Sprite sprite;

    Crosshair(const sf::Texture& texture) {
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);
    }

    void updatePosition(const sf::Vector2i& mousePos) {
        sprite.setPosition(sf::Vector2f(mousePos));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

int main() {
    srand(time(0));

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Juego de Crosshair");

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("C:/Mavi/Unidad4_Assets/et.png")) {
        std::cerr << "Error al cargar la imagen del enemigo" << std::endl;
        return -1;
    }

    sf::Texture crosshairTexture;
    if (!crosshairTexture.loadFromFile("C:/Mavi/Unidad4_Assets/crosshair.png")) {
        std::cerr << "Error al cargar la imagen de la mira" << std::endl;
        return -1;
    }

    Crosshair crosshair(crosshairTexture);

    std::vector<Enemy> enemies;
    for (int i = 0; i < 5; ++i) {
        enemies.push_back(Enemy(enemyTexture));
    }

    int defeatedEnemies = 0;
    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!gameOver) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            crosshair.updatePosition(mousePos);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (auto& enemy : enemies) {
                    if (!enemy.isDefeated) {
                        enemy.checkCollision(mousePos);
                        if (enemy.isDefeated) {
                            defeatedEnemies++;
                            std::cout << "Enemigos derrotados: " << defeatedEnemies << std::endl;
                            if (defeatedEnemies >= 5) {
                                gameOver = true;
                                std::cout << "¡Has ganado el juego!" << std::endl;
                            }
                            break;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        for (auto& enemy : enemies) {
            enemy.draw(window);
        }

        crosshair.draw(window);

        window.display();
    }

    return 0;
}
