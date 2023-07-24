#pragma once
#include "Scene.h"

class GameScene : public Scene {
public:
    GameScene(float width, float height);
    ~GameScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;
};
