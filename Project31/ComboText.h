#pragma once
#include <SFML/Graphics.hpp>

class ComboText {
private:
    sf::Text numberText;
    sf::Text comboText;
    sf::Font font;
    float scale;
    int combo;

public:
    ComboText() : scale(1.0f), combo(0) {
        numberText.setFont(font);
        comboText.setFont(font);

        comboText.setString("Combo");
        comboText.setCharacterSize(24);
        comboText.setFillColor(sf::Color::White);
        comboText.setPosition(10, 70); 

        numberText.setCharacterSize(50); 
        numberText.setFillColor(sf::Color::White); 
        numberText.setPosition(10, 10);
    }

    void setCombo(int newCombo) {
        combo = newCombo;
        numberText.setString(std::to_string(combo));
        // 콤보가 변경되면 애니메이션을 위해 스케일을 리셋
        scale = 1.0f;
    }

    void animation(float dt) {
        // 애니메이션 효과 (예: 스케일 증가)
        scale += 0.5f * dt; // 스케일 변경 속도
        if (scale > 2.0f) scale = 1.0f; // 최대 크기를 넘으면 리셋
        numberText.setCharacterSize(50 * scale);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(numberText);
        window.draw(comboText);
    }
};
