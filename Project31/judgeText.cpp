#include "JudgeText.h"

void JudgeText::setJudgement(int judge) {
    judgement = judge;

    switch (judge) {
    case 0:
        judgeText.setString("MISS");
        judgeText.setFillColor(sf::Color(128,128,128));
        scale = 1.0f;
        break;
    case 1:
        judgeText.setString("BAD");
        judgeText.setFillColor(sf::Color(102, 0, 102));
        scale = 1.0f;
        break;
    case 2:
        judgeText.setString("GOOD");
        judgeText.setFillColor(sf::Color(255, 153, 0));
        scale = 1.2f;
        break;
    case 3:
        judgeText.setString("COOL");
        judgeText.setFillColor(sf::Color(153, 255, 51));
        scale = 1.2f;
        break;
    case 4:
        judgeText.setString("KOOL");
        scale = 1.2f;
        judgeText.setFillColor(sf::Color(0, 255, 0));
        break;
    }
    alpha_flag = 1.0f;
    judgeText.setCharacterSize((int)(textSize * scale));
    float centerX = x - judgeText.getLocalBounds().width / 2.0f;
    judgeText.setPosition(centerX, y);
}

void JudgeText::animation(float dt) {
    sf::Color currentColor = judgeText.getFillColor();
    if (alpha_flag <= 0) {
        printf("flag on\n");
        alpha_flag = 0;
        judgeText.setFillColor(sf::Color(currentColor.r,currentColor.g, currentColor.b, 0));
        return;
    }
    else 
        judgeText.setFillColor(sf::Color(currentColor.r, currentColor.g, currentColor.b, 255));
    

    if (scale <= 1.0f) {
        scale = 1.0f;
        return;
    }
    alpha_flag -= 1.5 * dt;
    scale -= 2.5f * dt;
    judgeText.setCharacterSize((int)(textSize * scale));

    float centerX = x - judgeText.getLocalBounds().width / 2.0f;
    judgeText.setPosition(centerX, y);
}

void JudgeText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(judgeText, states);
}

void JudgeText::setPosition(float x, float y) {
    this->x = x;
    this->y = y;

    float centerX = x - judgeText.getLocalBounds().width / 2.0f;
    judgeText.setPosition(centerX, y);
}

void JudgeText::setFont(sf::Font& font) {
    this->font = font;
    judgeText.setFont(font);

    judgeText.setString("");
    judgeText.setCharacterSize(textSize);
    judgeText.setFillColor(this->color);

    float centerX = x - judgeText.getLocalBounds().width / 2.0f;
    judgeText.setPosition(centerX, y);
}
