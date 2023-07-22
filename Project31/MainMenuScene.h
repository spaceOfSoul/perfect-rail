#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

class MainMenuScene : public Scene {
private:
    sf::Font font;
    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::Text buttonText;

public:
    MainMenuScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};
