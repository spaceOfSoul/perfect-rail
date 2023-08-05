#pragma once
#include <SFML/Graphics.hpp>

class ComboText : public sf::Drawable {
public:
    ComboText(sf::Color color, float x, float y) : scale(1.0f), combo(0),color(color),x(x),y(y) {}
    void setCombo(int newCombo);
    void animation(float dt);
    void setFont(sf::Font&);
    void setPosition(float x, float y);

private:
    sf::Text numberText;
    sf::Text comboText;
    sf::Font font;
    sf::Color color;
    float scale;
    float x, y;
    int combo;

    int comboSize_num = 80;
    int comboSize_txt = 24;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
