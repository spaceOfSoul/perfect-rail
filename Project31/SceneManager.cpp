#include "SceneManager.h"

SceneManager::SceneManager(std::map<std::string, Scene*> scenes) {
    this->scenes = scenes;
}

void SceneManager::setScreen(std::string sceneName) {
    this->currentScreen = scenes[sceneName];
}

void SceneManager::handleInput(sf::Event event, sf::RenderWindow& window) {
    Signal signal = currentScreen->handleInput(event, window);
    switch (signal)
    {
    case Signal::None:
        break;
    case Signal::GoToMainMenu:
        setScreen("mainMenu");
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

void SceneManager::update(float dt) {
    currentScreen->update(dt);
}

void SceneManager::draw(sf::RenderWindow& window) {
    currentScreen->draw(window);
}
