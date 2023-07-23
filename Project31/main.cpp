#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "MainMenuScene.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Perfect Rail");

    bool fullscreen = true;

    MainMenuScene mainMenu(window.getSize().x, window.getSize().y);
    sf::Clock clock;

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
                window.create(fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(800, 600),
                    "Perfect Rail",
                    fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
            }

            if(event.type)

            // 목록 화면 이벤트
                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        mainMenu.MoveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        mainMenu.MoveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Return)
                    {
                        int pressedItem = mainMenu.GetPressedItem();

                        if (pressedItem == 0)
                        {
                            printf("Play button has been pressed\n");
                        }
                        else if (pressedItem == 1)
                        {
                            printf("Option button has been pressed\n");
                        }
                        else if (pressedItem == 2)
                        {
                            window.close();
                        }
                    }
                }

            // 게임 내의 이벤트
            // 이벤트 전달 메소드 쓸 예정


            // 설정 이벤트
            // 이벤트 전달 메소드 쓸 예정
        }

        float dt = clock.restart().asSeconds(); // deltaTime
        // Update the scene


        //Draw the scene
        window.clear();
        mainMenu.draw(window);
        window.display();
    }

    return 0;
}
