#pragma once
#include <SFML/Graphics.hpp>

class Note : public sf::Drawable, public sf::Transformable {
public:
    Note(int key, float x, float y, float size, sf::Color color, bool isLong = false)
        : key(key), position(x,y),size(size), isLong(isLong),color(color) {};

private:
    int key;
    sf::Vector2f position;
    sf::Color color;
    float size;
    bool isLong;
};
