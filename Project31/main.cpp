#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "MainMenuScene.h"
#include "SongMenuScene.h"
#include "SceneManager.h"

int main()
{
    const unsigned int window_width = 800;
    const unsigned int window_height = 600;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Perfect Rail");

    bool fullscreen = true;
    int screen_num = 0;

    std::map<std::string, Scene*> scenes;
    scenes["mainMenu"] = new MainMenuScene(window.getSize().x, window.getSize().y);
    scenes["songMenu"] = new SongMenuScene(window.getSize().x, window.getSize().y);

    SceneManager scene_manager(scenes);

    sf::Clock clock;

    scene_manager.setScreen("mainMenu");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // game 전반의 이벤트
            if (event.type == sf::Event::Closed)
                window.close();

            // 전체화면 전환
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            {
                fullscreen = !fullscreen;
                window.create(fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(window_width, window_height),
                    "Perfect Rail",
                    fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
            }

            // Scene handle
            scene_manager.handleInput(event, window);
        }

        float dt = clock.restart().asSeconds(); // deltaTime
        // Update the scene
        scene_manager.update(dt);

        //Draw the scene
        window.clear();
        scene_manager.draw(window);
        window.display();
    }

    return 0;
}
