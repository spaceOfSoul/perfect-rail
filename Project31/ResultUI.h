#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class ResultUI : public sf::Drawable {
public:
    ResultUI(float width, float height, sf::Font& font);
    void setResult(double accuracy, int score, int maxCom, std::array<int, 5> targetPass);

private:
    sf::RectangleShape backGround;

    sf::Text Title;

    sf::Text rank_txt;
    sf::Text Rank;

    std::string judge_str[5] = {"KOOL : ","COOL : ", "GOOD : ","BAD : ","MISS : "};
    sf::Text judeges_txt[5];
    sf::Text judeges[5];

    double accuracy;
    sf::Text acc_txt;
    sf::Text acc;

    int score_num;
    sf::Text score_txt;
    sf::Text score;

    int combo;
    sf::Text combo_txt;
    sf::Text maxCombo;

    sf::Font font;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};