#include "ResultUI.h"
ResultUI::ResultUI(float width, float height, sf::Font& font) {
	this->font = font;
	new_result = false;
	accuracy = 100.0;
	score_num = 0;
	combo = 0;
	backGround.setPosition(0, 0);
	backGround.setSize(sf::Vector2f(width, height));
	backGround.setFillColor(sf::Color::Black);
}

void ResultUI::setResult(double accuracy, int score, int maxCom, std::array<int, 5> targetPass, bool is_new) {
#pragma region initializeRegion
	Title.setFont(font);
	Title.setPosition(sf::Vector2f(20, 10));
	Title.setCharacterSize(60);
	Title.setFillColor(sf::Color::White);
	Title.setString("Result");

	rank_txt.setFont(font);
	rank_txt.setPosition(sf::Vector2f(20, 100));
	rank_txt.setCharacterSize(40);
	rank_txt.setFillColor(sf::Color::White);
	rank_txt.setString("RANK : ");

	Rank.setFont(font);
	Rank.setPosition(sf::Vector2f(150, 150));
	Rank.setCharacterSize(200);
	Rank.setString("F");
	Rank.setFillColor(sf::Color(71, 71, 71));

	newRecord.setFont(font);
	newRecord.setPosition(sf::Vector2f(120, 350));
	newRecord.setCharacterSize(30);
	newRecord.setString("New Record");
	newRecord.setFillColor(sf::Color(255, 255, 0));

	acc_txt.setFont(font);
	acc_txt.setPosition(sf::Vector2f(380, 350));
	acc_txt.setCharacterSize(30);
	acc_txt.setFillColor(sf::Color::White);
	acc_txt.setString("Accuracy : ");

	combo_txt.setFont(font);
	combo_txt.setPosition(sf::Vector2f(380, 400));
	combo_txt.setCharacterSize(30);
	combo_txt.setFillColor(sf::Color::White);
	combo_txt.setString("Max Combo : ");

	score_txt.setFont(font);
	score_txt.setPosition(sf::Vector2f(380, 450));
	score_txt.setCharacterSize(30);
	score_txt.setFillColor(sf::Color::White);
	score_txt.setString("Score : ");

	acc.setFont(font);
	acc.setPosition(sf::Vector2f(600, 350));
	acc.setCharacterSize(30);
	acc.setFillColor(sf::Color::White);
	acc.setString("100.00%");

	maxCombo.setFont(font);
	maxCombo.setPosition(sf::Vector2f(600, 400));
	maxCombo.setCharacterSize(30);
	maxCombo.setFillColor(sf::Color::White);
	maxCombo.setString("2048");

	this->score.setFont(font);
	this->score.setPosition(sf::Vector2f(600, 450));
	this->score.setCharacterSize(30);
	this->score.setFillColor(sf::Color::White);
	this->score.setString("5605602");

	for (int i = 0; i < 5; i++) {
		judeges_txt[i].setFont(font);
		judeges_txt[i].setPosition(sf::Vector2f(380, 70 + 50 * i));
		judeges_txt[i].setCharacterSize(30);
		judeges_txt[i].setFillColor(sf::Color::White);
		judeges_txt[i].setString(judge_str[i]);
	}

	for (int i = 0; i < 5; i++) {
		judeges[i].setFont(font);
		judeges[i].setPosition(sf::Vector2f(500, 70 + 50 * i));
		judeges[i].setCharacterSize(30);
		judeges[i].setFillColor(sf::Color::White);
		judeges[i].setString(std::to_string(1000));
	}
#pragma endregion

	std::string accurateStr = std::to_string(accuracy);
	accurateStr = accurateStr.substr(0, accurateStr.find(".") + 3) + "%";
	acc.setString(accurateStr);

	if (accuracy >= 95) { // S
		Rank.setString("S");
		Rank.setFillColor(sf::Color::Yellow);
	}
	else if(accuracy >= 90) { // A
		Rank.setString("A");
		Rank.setFillColor(sf::Color::Green);
	}
	else if (accuracy >= 81.5) { // B
		Rank.setString("B");
		Rank.setFillColor(sf::Color(0,0,204));
	}
	else if (accuracy >= 72) { // C
		Rank.setString("C");
		Rank.setFillColor(sf::Color(102, 30, 103));
	}
	else if(accuracy >= 65) { // D
		Rank.setString("D");
		Rank.setFillColor(sf::Color(122, 0, 0));
	}
	else { // F
		Rank.setString("F");
		Rank.setFillColor(sf::Color(51, 51, 41));
	}

	this->score.setString(std::to_string(score));
	maxCombo.setString(std::to_string(maxCom));

	for (int i = 0; i < 5; i++) {
		judeges[i].setString(std::to_string(targetPass[4-i]));
	}
	new_result = is_new;
}

void ResultUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(backGround, states);

	target.draw(Rank, states);
	target.draw(acc, states);

	target.draw(Title, states);
	target.draw(rank_txt, states);
	target.draw(acc_txt, states);
	target.draw(score_txt, states);
	target.draw(combo_txt, states);

	for (int i = 0; i < 5; i++) {
		target.draw(judeges_txt[i], states);
		target.draw(judeges[i], states);
	}

	target.draw(maxCombo, states);
	target.draw(score, states);
}