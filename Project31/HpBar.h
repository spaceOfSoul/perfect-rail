#pragma once

#include <SFML/Graphics.hpp>

class HpBar : public sf::Drawable {
public:
    HpBar(float x, float y, float width, float height, sf::Font font, int font_size);
    void setHP(double hp);
private:
    sf::Vector2f pos;
    double hp;
    sf::Color hpColor;
    float full_hp_height;
    float hp_height;
    float hp_y_pos;
    float height;
    float width;
    sf::Font font;

    //render objs
    sf::RectangleShape pannel_rect;
    sf::RectangleShape hp_rect;
    sf::RectangleShape back_hp_pannel;
    sf::Text label;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};