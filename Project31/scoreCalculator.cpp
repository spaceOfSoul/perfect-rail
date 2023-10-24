#include "scoreCalculator.h"

/*
* return std::pair<char, sf::Color>
* rank : char
* color : sf::Color
*/
std::pair<char, sf::Color> decideRank(double acc) {
    std::pair<char, sf::Color> rank_data;

    if (acc >= 95) { // S
        rank_data.first = 'S';
        rank_data.second = sf::Color::Yellow;
    }
    else if (acc >= 90) { // A
        rank_data.first = 'A';
        rank_data.second = sf::Color::Green;
    }
    else if (acc >= 81.5) { // B
        rank_data.first = 'B';
        rank_data.second = sf::Color(0, 0, 204);
    }
    else if (acc >= 72) { // C
        rank_data.first = 'C';
        rank_data.second = sf::Color(102, 30, 103);
    }
    else if (acc >= 65) { // D
        rank_data.first = 'D';
        rank_data.second = sf::Color(122, 0, 0);
    }
    else { // F
        rank_data.first = 'F';
        rank_data.second = sf::Color(51, 51, 41);
    }

    return rank_data;
}