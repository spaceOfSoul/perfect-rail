#pragma once
#include "Scene.h"
#include "AlbumArt.h"
#include "AudioManager.h"

#include <filesystem>
#include <vector>
#include <stdio.h>

struct SongInfo {
    std::string songNameStr;
    std::string imagePath;
    std::string songPath;
};

class SongMenuScene : public Scene {
private:
    sf::Font font;

    AudioManager& am;

    std::vector<SongInfo> songInfos;
    std::unique_ptr<AlbumArt> albumImage;
    int selectedItemIndex = 0;

    float width;
    float height;

public:
    SongMenuScene(float width, float height);
    ~SongMenuScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

    int GetPressedItem() { return selectedItemIndex; }
};
