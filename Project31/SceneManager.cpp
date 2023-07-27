#include "SceneManager.h"
#include "GameScene.h"

void SceneManager::registerScenes(std::map<std::string, Scene*> scenes) {
    this->scenes = scenes;
    this->currentScreen = nullptr;
}

void SceneManager::setScreen(std::string sceneName) {
    if (this->currentScreen != nullptr)
        this->currentScreen->onDeactivate();
    this->currentScreen = scenes[sceneName];
    this->currentScreen->onActivate();
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
        setScreen("gameScene");
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

void SceneManager::setGameScene(const SongInfo& songInfo, int difficultyIndex) {
    this->currentPlaySong = songInfo;
    this->currentDifficultyIndex = difficultyIndex;
}
