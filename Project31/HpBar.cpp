#include "HpBar.h"
// hp bar object

HpBar::HpBar(float x, float y, float width, float height, sf::Font font, int font_size) {
    pos.x = x;
    pos.y = y;
    hp = 100;
    hpColor = sf::Color::Red;
    this->height = height;
    this->width = width;

    hp_height = this->height - 40;
    full_hp_height = this->height - 40;

    pannel_rect.setFillColor(sf::Color(128, 128, 128));
    pannel_rect.setSize(sf::Vector2f(width, height));
    pannel_rect.setPosition(x, y);

    hp_rect.setFillColor(sf::Color::Red);
    hp_rect.setSize(sf::Vector2f(width - 10, hp_height));
    hp_y_pos = y + 30;
    hp_rect.setPosition(x + 5, hp_y_pos);

    back_hp_pannel.setFillColor(sf::Color(51, 51, 51));
    back_hp_pannel.setSize(sf::Vector2f(width - 10, hp_height));
    back_hp_pannel.setPosition(x + 5, hp_y_pos);

    this->font = font;
    label.setFont(this->font);
    label.setString("HP");
    label.setCharacterSize(font_size);
    label.setFillColor(sf::Color::Black);
    label.setPosition(x + 2, y + 10);
    label.setStyle(sf::Text::Bold);
}

void HpBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(pannel_rect, states);
    target.draw(back_hp_pannel, states);
    target.draw(hp_rect, states);
    target.draw(label, states);
}

void HpBar::setHP(double hp) {
    double hpHeightRate = hp / (double)100;

    if (hpHeightRate<0)
        hp_height = 0;
    else
        hp_height = full_hp_height * hpHeightRate;

    hp_rect.setSize(sf::Vector2f(width - 10, hp_height));

    hp_y_pos = (full_hp_height - hp_height);
    hp_rect.setPosition(pos.x + 5, pos.y + 30 + hp_y_pos);
}