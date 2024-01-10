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
        text_result[i].setPosition(x+75, y + i * 30 +4);
        text_result[i].setString("");
        text_result[i].setCharacterSize(13);
        text_result[i].setFillColor(sf::Color::White);

        text_name[i].setFont(this->font);
        text_name[i].setPosition(x+19, y + i * 30 + 4);
        text_name[i].setString("");
        text_name[i].setCharacterSize(15);
        text_name[i].setFillColor(sf::Color::White);

        text_rank[i].setFont(this->font);
        text_rank[i].setPosition(x, y + i * 30);
        text_rank[i].setString("");
        text_rank[i].setCharacterSize(20);
        text_rank[i].setFillColor(sf::Color::White);

        itemShape[i].setFillColor(sf::Color(36,36,36));
        itemShape[i].setPosition(x, y + i * 30);
        itemShape[i].setSize(sf::Vector2f(285,28));
    }
}

void HighscorePannel::setScores(Results& results) {
    int result_size = results.size();
    ResultData result;
    std::ostringstream result_ss, rank_ss, name_ss;

    for (int i = 0; i < result_size; i++) {
        result = results[i];

        result_ss << "score : " << result.score << "\tmax combo : " << result.maxCom;
        text_result[i].setString(result_ss.str());
        result_ss.str("");
        result_ss.clear();

        
        rank_ss << decideRank(result.accuracy).first;
        text_rank[i].setString(rank_ss.str());
        text_rank[i].setFillColor(decideRank(result.accuracy).second );
        rank_ss.str("");
        rank_ss.clear();

        name_ss << result.username;
        text_name[i].setString(name_ss.str());
        name_ss.str("");
        name_ss.clear();
    }
    for (int i = result_size; i < 10; i++) {
        text_result[i].setString("");
        text_rank[i].setString("");
        text_name[i].setString("");
    }
}

