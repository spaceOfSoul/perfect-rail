#pragma once
#include "Scene.h"

class MainMenuScene : public Scene {
public:
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};
