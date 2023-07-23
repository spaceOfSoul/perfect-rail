#pragma once
#include "Scene.h"

#include <filesystem>
#include <vector>
#include <stdio.h>

class SongMenuScene : public Scene {
private:
    sf::Font font;
    std::vector<sf::Text> song_list;
    int selectedItemIndex;

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
