#include "ComboText.h"

void ComboText::setCombo(int newCombo) {
    combo = newCombo;
    if (combo) {
        numberText.setString(std::to_string(combo));
        scale = 1.5f;
        numberText.setCharacterSize((int)(50 * scale));
        comboText.setString("Combo");
    }
    else {
        numberText.setString("");
        comboText.setString("");
    }
    
    float centerX_number = x - numberText.getLocalBounds().width / 2.0f;
    numberText.setPosition(centerX_number, y);
}

void ComboText::animation(float dt) {
    if (scale <= 1.0f) {
        scale = 1.0f;
        return;
    }
    scale -= 0.5f * dt; 
    numberText.setCharacterSize((int)(50 * scale));
    float centerX_number = x - numberText.getLocalBounds().width / 2.0f;
    numberText.setPosition(centerX_number, y);
}

void ComboText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(numberText, states);
    target.draw(comboText, states);
}

void ComboText::setPosition(float x, float y) {
    this->x = x;
    this->y = y;

    float centerX_number = x - numberText.getLocalBounds().width / 2.0f;
    numberText.setPosition(centerX_number, y);

    float comboCenterX = x - comboText.getLocalBounds().width / 2.0f;
    float y_pos = y + comboSize_num + 5;
    comboText.setPosition(comboCenterX, y_pos);
}


void ComboText::setFont(sf::Font& font) {
    this->font = font;
    numberText.setFont(font);
    comboText.setFont(font);

    numberText.setString(std::to_string(combo));
    numberText.setCharacterSize(comboSize_num);
    numberText.setFillColor(this->color);
    float centerX_number = x - numberText.getLocalBounds().width / 2.0f;
    numberText.setPosition(centerX_number, y);
    
    comboText.setString("Combo");
    comboText.setCharacterSize(comboSize_txt);
    comboText.setFillColor(this->color);
    float comboCenterX = x - comboText.getLocalBounds().width / 2.0f;
    float y_pos = y + comboSize_num + 5;
    comboText.setPosition(comboCenterX, y_pos);
}