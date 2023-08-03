#pragma once
#include <SFML/Graphics.hpp>

class Note : public sf::Drawable {
public:
    Note(int key, float x, float y, float size, sf::Color color, bool isLong = false)
        : key(key), position(x, y), size(size), isLong(isLong), color(color) {
        shape.setSize(sf::Vector2f(size, size));
        shape.setFillColor(color);
        shape.setPosition(x, y);
    };
    int key;
    sf::Vector2f position;
    sf::Color color;
    float size;
    bool isLong;

private:
    sf::RectangleShape shape;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(shape, states);
    }
};
