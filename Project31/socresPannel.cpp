#include "scoresPannel.h"

HighscorePannel::HighscorePannel(float x, float y, sf::Font font) {
    this->x = x;
    this->y = y;
    this->font = font;
    /*resgionShaape.setSize(sf::Vector2f(25, 25));
    resgionShaape.setPosition(x, y);
    resgionShaape.setFillColor(sf::Color::White);*/
    for (int i = 0; i < 10; i++) {
        text_result[i].setFont(this->font);
        text_result[i].setPosition(x, y + i * 27);
        text_result[i].setString("");
        text_result[i].setCharacterSize(13);
        text_result[i].setFillColor(sf::Color::White);
    }
}

void HighscorePannel::setScores(Results& results) {
    int result_size = results.size();
    ResultData result;
    std::ostringstream oss;

    for (int i = 0; i < result_size; i++) {
        result = results[i];
        oss << result.username << "\n" << decideRank(result.accuracy).first << "\tscore : " << result.score << "\tmax combo : " << result.maxCom;
        text_result[i].setString(oss.str());
        oss.str("");
        oss.clear();
    }
    for (int i = result_size; i < 10; i++) {
        text_result[i].setString("");
    }
}

