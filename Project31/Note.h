#pragma once
#include <SFML/Graphics.hpp>

class Note : public sf::Drawable {
public:
    Note(int key, float x, float y, float size, sf::Color color, int time, bool isLong = false)
        : key(key), position(x, y), size(size), isLong(isLong), color(color), time(time) {
        shape.setSize(sf::Vector2f(size, 20));
        shape.setFillColor(color);
        shape.setPosition(x, y);
    };
    int key;
    sf::Vector2f position;
    sf::Color color;
    float size;
    bool isLong;

    int time;

    // getter
    const sf::Vector2f& getPosition() const { return position; }

    //setter
    void setPosition(const sf::Vector2f& pos) {
        position = pos;
        shape.setPosition(pos);
    }

private:
    sf::RectangleShape shape;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(shape, states);
    }
};
