#pragma once

#include <SFML/Graphics.hpp>

#include "AudioManager.h"
#include "signal.h"
#include "Scene.h"
#include "options.h"
#include "SettingsManager.h"

#define OPTION_ITEM 7

class OptionScene : public Scene
{
private:
    AudioManager& am;
    SettingsManager& sm;

    sf::Font font;
    sf::Text titleText;
    sf::Text menus[OPTION_ITEM];
    sf::RectangleShape startButton;
    int selectedItemIndex = 0;
    const int fontSize = 24;

public:
    OptionScene(float width, float height);
    ~OptionScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;

    void onActivate();
    void onDeactivate();

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
};

