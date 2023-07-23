#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "Scene.h"

class SceneManager {
public:
    SceneManager(std::map<std::string, Scene*> scenes) {
        this->scenes = scenes;
    }

    void setScreen(std::string sceneName) {
        this->currentScreen = scenes[sceneName];
    }

    void handleInput(sf::Event event, sf::RenderWindow& window) {
        Signal signal = currentScreen->handleInput(event, window);
        switch (signal)
        {
        case Signal::None:
            break;
        case Signal::GoToSongMenu:
            setScreen("songMenu");
            break;
        case Signal::GoToOptionMenu:
            break;
        case Signal::GoToPlayScene:
            break;
        case Signal::GoToResult:
            break;
        case Signal::Exit:
            window.close();
            break;
        default:
            break;
        }
    }

    void update(float dt) {
        currentScreen->update(dt);
    }

    void draw(sf::RenderWindow& window) {
        currentScreen->draw(window);
    }

private:
    Scene* currentScreen;
    std::map<std::string,Scene*> scenes;
};
