#include "NameInputUI.h"

NameInputUI::NameInputUI(int x, int y, int offset, int current_chracter = 0, int current_size = 50, std::string username) {
	this->x_position = x;
	this->y_position = y;
	this->x_offset = offset;
	this->current_chracter = current_chracter;
	this->character_size = current_size;
	this->username = username;

	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음!");
	}

	for (int i = 0; i < nameLenth; i++) {
		// txt setting
		txts[i].setFont(font);
		txts[i].setColor(sf::Color::White);
		txts[i].setCharacterSize(character_size);

		// rectangle setting
		rects[i].setFillColor(sf::Color::White);
		rects[i].setPosition(sf::Vector2f(x_offset*100, y_position + character_size/2));
		rects[i].setSize(sf::Vector2f(character_size, character_size/2));
	}
}

void NameInputUI::setChar(int index, bool upOrDown) {

}