#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Scene.h"
#include "SongInfo.h"

class SceneManager {
public:
    static SceneManager& getInstance()
    {
        static SceneManager instance;
        return instance;
    }

    void handleInput(sf::Event event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void setScreen(const int sceneName);

    void registerScenes(std::vector<Scene*>& scenes);

    void setGameScene(const SongInfo& songInfo, int difficultyIndex);

    // 객체에 대한 복사, 이동을 막음.
    SceneManager(SceneManager const&) = delete;             // Copy construct
    SceneManager(SceneManager&&) = delete;                  // Move construct
    SceneManager& operator=(SceneManager const&) = delete;  // Copy assign
    SceneManager& operator=(SceneManager&&) = delete;      // Move assign

    // for play Scene
    SongInfo currentPlaySong;
    int currentDifficultyIndex;
    int currentSceneNum;
private:
    SceneManager() = default;
    Scene* currentScreen;
    std::vector<Scene*> scenes;
};
