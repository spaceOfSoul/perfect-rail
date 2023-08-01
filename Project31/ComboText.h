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
        // �޺��� ����Ǹ� �ִϸ��̼��� ���� �������� ����
        scale = 1.0f;
    }

    void animation(float dt) {
        // �ִϸ��̼� ȿ�� (��: ������ ����)
        scale += 0.5f * dt; // ������ ���� �ӵ�
        if (scale > 2.0f) scale = 1.0f; // �ִ� ũ�⸦ ������ ����
        numberText.setCharacterSize(50 * scale);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(numberText);
        window.draw(comboText);
    }
};
