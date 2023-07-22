#include <SFML/Graphics.hpp>
#include "MainMenuScene.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Perfect Rail");

    bool fullscreen = true;

    MainMenuScene mainMenu;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // 전체화면 전환
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            {
                fullscreen = !fullscreen;
                window.create(fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(800, 600),
                    "Perfect Rail",
                    fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
            }
        }

        // Update the scene
        float dt = clock.restart().asSeconds(); // deltaTime
        mainMenu.update(dt);

        //Draw the scene
        window.clear();

        mainMenu.draw(window);
        window.display();
    }

    return 0;
}
