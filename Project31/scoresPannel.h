#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "playResult.h"
#include "scoreCalculator.h"
class HighscorePannel : public sf::Drawable {
public:
    HighscorePannel(float x, float y, sf::Font font);
    void setScores(Results& results);
private:
    sf::RectangleShape resgionShaape;
    sf::Text text_result[10];
    sf::Text text_rank[10];
    sf::Text text_name[10];
    sf::RectangleShape itemShape[10];
    sf::Font font;
    float x, y; // Pos of high score pannel

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        //target.draw(resgionShaape, states);
        for (int i = 0; i < 10; i++) {
            target.draw(itemShape[i], states);
            target.draw(text_result[i], states);
            target.draw(text_rank[i], states);
            target.draw(text_name[i], states);
        }
    }
};