#pragma once
#include "Scene.h"

class SongMenuScene : public Scene {
public:
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};
