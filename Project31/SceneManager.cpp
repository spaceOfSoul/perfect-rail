#include "SceneManager.h"
#include "GameScene.h"

void SceneManager::registerScenes(std::vector<Scene*>& scenes) {
    this->scenes = scenes;
    this->currentScreen = nullptr;
}

void SceneManager::setScreen(int sceneNum) {
    if (this->currentScreen != nullptr)
        this->currentScreen->onDeactivate();
    printf("set %d\n", sceneNum);
    this->currentScreen = scenes[sceneNum];
    this->currentScreen->onActivate();
}

void SceneManager::handleInput(sf::Event event, sf::RenderWindow& window) {
    Signal signal = currentScreen->handleInput(event, window);
    switch (signal)
    {
    case Signal::None:
        break;
    case Signal::GoToMainMenu:
        setScreen(0);
        break;
    case Signal::GoToSongMenu:
        setScreen(1);
        break;
    case Signal::GoToOptionMenu:
        setScreen(3);
        break;
    case Signal::GoToPlayScene:
        setScreen(2);
        break;
    case Signal::DebugCommandActivated:
        setScreen(4);
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
