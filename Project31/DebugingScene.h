#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

// test include
//#include "NameInputUI.h"
#include "KeySettingModal.h"

class DebuggingScene : public Scene {
private:
	sf::Font font;
    int width, height;
    KeySettingModal setting_ui;
	
public:
    DebuggingScene(float width, float height, sf::Font& font);
    ~DebuggingScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;

    void onActivate();
    void onDeactivate();
};