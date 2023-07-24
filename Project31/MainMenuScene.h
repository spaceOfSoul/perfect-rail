#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "signal.h"
#include "AudioManager.h"

#define MAX_OF_ITEM 3

class MainMenuScene : public Scene {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text menu_texts[MAX_OF_ITEM];
    sf::RectangleShape startButton;
    AudioManager& am;
    int selectedItemIndex = 0;
    const int fontSize = 24;


public:
    MainMenuScene(float width, float height);
    ~MainMenuScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow &window) override;

    void MoveUp();
    void MoveDown();

    int GetPressedItem() { return selectedItemIndex; }
};
