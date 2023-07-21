#include "ScreenManager.h"
#include "Scene.h"

#include <SFML/Graphics.hpp>
#include <memory>

class ScreenManager {
public:
    void setScreen(std::unique_ptr<Scene> newScreen) {
        currentScreen = std::move(newScreen);
    }

    void update(float dt) {
        if (currentScreen)
            currentScreen->update(dt);
    }

    void draw(sf::RenderWindow& window) {
        if (currentScreen)
            currentScreen->draw(window);
    }

private:
    std::unique_ptr<Scene> currentScreen;
};