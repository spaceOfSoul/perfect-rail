#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

#define MAX_OF_ITEM 3

class MainMenuScene : public Scene {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text menu_texts[MAX_OF_ITEM];
    sf::RectangleShape startButton;
    int selectedItemIndex;
    const int fontSize = 24;

public:
    MainMenuScene(float width, float height);
    ~MainMenuScene();

    void update(float dt);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    void draw(sf::RenderWindow& window) override;
};
