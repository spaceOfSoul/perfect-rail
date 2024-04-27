#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Scene.h"
#include "signal.h"
#include "AudioManager.h"

//#define MAX_OF_ITEM 3
#define MAX_OF_ITEM 2

class MainMenuScene : public Scene {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text menu_texts[MAX_OF_ITEM];
    sf::RectangleShape startButton;
    AudioManager& am;
    int selectedItemIndex = 0;
    const int fontSize = 24;
    float width;
    float height;

    std::vector<sf::Keyboard::Key> testSceneCommands;
    std::vector<sf::Keyboard::Key> currentInputSequence;
    bool hiddenSceneActivate;

    bool checkForHiddenCommand(sf::Keyboard::Key keyPressed);

    std::string cat_path[3] = {
        "sprites/base.png",
        "sprites/base_left.png",
        "sprites/base_right.png"
    };
    sf::Sprite cat, leftPaw, rightPaw;
    sf::Texture cat_texture[3];
    sf::RectangleShape blackLine;

public:
    MainMenuScene(float width, float height, sf::Font& font);
    ~MainMenuScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow &window) override;

    void onActivate();
    void onDeactivate();

    void MoveUp();
    void MoveDown();
};
