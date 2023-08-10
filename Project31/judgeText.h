#pragma once
#include <SFML/Graphics.hpp>

class JudgeText : public sf::Drawable {
public:
    JudgeText(sf::Color color, float x, float y) : scale(1.0f), judgement(""), color(color), x(x), y(y) {}

    void setJudgement(int judge);
    void animation(float dt);
    void setFont(sf::Font&);
    void setPosition(float x, float y);
private:
    sf::Text judgeText;
    sf::Font font;
    sf::Color color;
    float scale;
    float alpha_flag;
    float x, y;
    std::string judgement;

    int textSize = 40;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
