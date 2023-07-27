#pragma once
#include "Scene.h"
#include "SongMenuScene.h"

#include "parse_data.h"

class GameScene : public Scene {
public:
    GameScene(float width, float height);
    ~GameScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;

    void onActivate();
    void onDeactivate();

    void setSongInfo(const SongInfo& songInfo, int difficultyIndex);

    void reset();

private:
    SongInfo songInfo;
    int difficultyIndex;

    std::string generateFilePath(const SongInfo& songInfo, int difficultyIndex);
};
