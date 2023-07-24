#pragma once
#include "Scene.h"
#include "AlbumArt.h"
#include "AudioManager.h"

#include <filesystem>
#include <vector>
#include <stdio.h>

class SongMenuScene : public Scene {
private:
    sf::Font font;

    AudioManager& am;

    std::vector<sf::Text> song_list;
    int selectedItemIndex = 0;
    std::vector<std::string> songImagePaths;
    std::unique_ptr<AlbumArt> albumImage;

public:
    SongMenuScene(float width, float height);
    ~SongMenuScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;

    void MoveUp();
    void MoveDown();

    int GetPressedItem() { return selectedItemIndex; }
};
