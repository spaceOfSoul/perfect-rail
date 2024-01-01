#include "DebugingScene.h"

DebuggingScene::DebuggingScene(float width, float height) : setting_ui(150, 175, 500, 250) {
    this->width = width;
    this->height = height;
}

DebuggingScene::~DebuggingScene() {

}


void DebuggingScene::update(float dt) {
    // ±¸ÇöºÎ
}

void DebuggingScene::onActivate() {
    char keys[5] = "DFJK";
    setting_ui.setAllkey(keys);
}

void DebuggingScene::onDeactivate() {

}

void DebuggingScene::draw(sf::RenderWindow& window) {
    window.draw(setting_ui);
}

Signal DebuggingScene::handleInput(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            return Signal::GoToMainMenu;

        if (event.key.code == sf::Keyboard::Left) {
            char keys[5] = "DFJK";
            setting_ui.setAllkey(keys);
        }
        else if (event.key.code == sf::Keyboard::Right) {
            char keys[5] = "AS;'";
            setting_ui.setAllkey(keys);
        }
    }
    return Signal::None;
}