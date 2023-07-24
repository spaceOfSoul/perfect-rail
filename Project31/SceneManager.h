#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Scene.h"

class SceneManager {
public:
    SceneManager(std::map<std::string, Scene*> scenes);

    void setScreen(std::string sceneName);
    void handleInput(sf::Event event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    Scene* currentScreen;
    std::map<std::string, Scene*> scenes;
};
