#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "MainMenuScene.h"
#include "SongMenuScene.h"
#include "GameScene.h"
#include "DebugingScene.h"

#include "SceneManager.h"
#include "AudioManager.h"
#include "OptionScene.h"
#include "SettingsManager.h"

int main()
{
    const unsigned int window_width = 800;
    const unsigned int window_height = 600;
    SettingsManager sm = SettingsManager::Instance();

    printf("music volume : %f", sm.GetMusicVolume());

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Perfect Rail");

    bool fullscreen = true;
    int screen_num = 0;

    AudioManager& am = AudioManager::Instance(); // 오디오 관리자

    // sounds load
    for (const auto& entry : std::filesystem::directory_iterator("sounds")) {
        std::string path = entry.path().string();

        // wav 파일이면 로드함.
        if (entry.path().extension() == ".wav") {
            am.LoadSound(path);
        }
    }

    //맵 목록
    std::map<std::string, Scene*> scenes;
    scenes["mainMenu"] = new MainMenuScene(window.getSize().x, window.getSize().y);
    scenes["songMenu"] = new SongMenuScene(window.getSize().x, window.getSize().y);
    scenes["gameScene"] = new GameScene(window.getSize().x, window.getSize().y);
    scenes["optionScene"] = new OptionScene(window.getSize().x, window.getSize().y);
    scenes["debugScene"] = new DebuggingScene(window.getSize().x, window.getSize().y);

    // 맵 관리자
    SceneManager& scene_manager = SceneManager::getInstance();
    scene_manager.registerScenes(scenes);

    scene_manager.setScreen("mainMenu");

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
