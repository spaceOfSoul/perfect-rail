#include "ScreenManager.h"

void ScreenManager::setScreen(std::unique_ptr<Scene> newScreen) {
    currentScreen = std::move(newScreen);
}

void ScreenManager::update(float dt) {
    if (currentScreen)
        currentScreen->update(dt);
}

void ScreenManager::draw(sf::RenderWindow& window) {
    if (currentScreen)
        currentScreen->draw(window);
}
