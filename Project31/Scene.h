#pragma once
#include <SFML/Graphics.hpp>

#include "signal.h"

class Scene {
public:
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual Signal handleInput(sf::Event event, sf::RenderWindow &window) = 0;
    virtual void onActivate() = 0;
    virtual void onDeactivate() = 0;
};
