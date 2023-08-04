#pragma once
#include <SFML/Graphics.hpp>
class NotePlate : public sf::Drawable {
public:
    NotePlate(float x, float y) {
        shapes[0].setSize(sf::Vector2f(25, 600));
        shapes[0].setPosition(x, y);
        shapes[0].setFillColor(sf::Color::White);

        shapes[1].setSize(sf::Vector2f(350, 125));
        shapes[1].setPosition(x + 25, y + 475);
        shapes[1].setFillColor(sf::Color::White);

        shapes[2].setSize(sf::Vector2f(25, 600));
        shapes[2].setPosition(x + 375, y);
        shapes[2].setFillColor(sf::Color::White);

        judgeLine.setSize(sf::Vector2f(350,20));
        judgeLine.setPosition(x + 25, y + 450);
        judgeLine.setFillColor(sf::Color(128,128,128));
    }

private:
    sf::RectangleShape shapes[3];
    sf::RectangleShape judgeLine;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (int i = 0; i < 3; ++i) {
            target.draw(shapes[i], states);
        }
        target.draw(judgeLine, states);
    }
};