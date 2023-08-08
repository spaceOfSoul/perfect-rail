#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "signal.h"


class ResultScene : public Scene {
private:
    sf::Font font;

    sf::Text rank;

    sf::Text miss;
    sf::Text bad;
    sf::Text good;
    sf::Text cool;
    sf::Text kool;

    sf::Text miss_count;
    sf::Text bad_count;
    sf::Text good_count;
    sf::Text cool_count;
    sf::Text kool_count;

public:
    ResultScene(float width, float height);
    ~ResultScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;

    void onActivate();
    void onDeactivate();

};
