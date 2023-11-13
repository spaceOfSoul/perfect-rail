#pragma once
#include <SFML/Graphics.hpp>
class DeadPannel : public sf::Drawable {
public:
    DeadPannel(float x, float y);
private:
    sf::RectangleShape resgionShaape;

    sf::Font font;

    sf::Text main_text;
    sf::Text sub_text;
    float x, y; // pos
    float height, width;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};