#pragma once
#include "Scene.h"

class GameScene : public Scene {
public:
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};
