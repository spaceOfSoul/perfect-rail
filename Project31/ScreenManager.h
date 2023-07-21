#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Scene.h"

class ScreenManager {
public:
    void setScreen(std::unique_ptr<Scene> newScreen);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<Scene> currentScreen;
};
