#include "NameInputUI.h"

NameInputUI::NameInputUI(int x, int y, int offset,int width, int height, int current_chracter, int character_size) {
	this->x_position = x;
	this->y_position = y;
	this->x_offset = offset;
	this->current_chracter = current_chracter;
	this->character_size = character_size;

	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음!");
	}

	for (int i = 0; i < nameLenth; i++) {
		// txt setting
		txts[i].setFont(font);
		txts[i].setFillColor(sf::Color::White);
		txts[i].setPosition(sf::Vector2f(x_position+x_offset+i*100, y_position));
		txts[i].setCharacterSize(character_size);

		// rectangle setting
		rects[i].setFillColor(sf::Color::White);
		rects[i].setPosition(sf::Vector2f(x_position+x_offset+i*100, y_position + character_size/3));
		rects[i].setSize(sf::Vector2f(character_size, character_size/4));
	}
	inform.setFont(font);
	inform.setFillColor(sf::Color::White);
	inform.setPosition(sf::Vector2f(x_position - character_size*1.5, y_position - character_size*2.5));
	inform.setCharacterSize(character_size);
	inform.setString("Plz write your name : ");

	backgroudShape.setFillColor(sf::Color(125, 125, 125, 125)); // r,g,b,a
	backgroudShape.setPosition(sf::Vector2f(0, 0));
	backgroudShape.setSize(sf::Vector2f(width, height));


	current_chracter = 'A';
	index = 0;
	username.append(std::to_string(current_chracter));
	txts[index].setString(username[index]);
}

void resizeString(std::string& str, size_t newSize) {
	if (newSize != 0 && newSize < str.size()) {
		str.resize(newSize);
	}
}

void NameInputUI::setChar(bool upOrDown) { // 문자 업다운
	if (upOrDown) {
		current_chracter++;

		if (current_chracter > 'Z')
			current_chracter = 'A';

		username[username.size()-1] = current_chracter;
		txts[username.size() - 1].setString(username[username.size() - 1]);
	}
	else {
		current_chracter--;

		if (current_chracter <'A')
			current_chracter = 'Z';

		username[username.size() - 1] = current_chracter;
		txts[username.size() - 1].setString(username[username.size() - 1]);
	}
}

void NameInputUI::setIndex(bool upOrDown){
	if (upOrDown) {
		resizeString(username, username.size() + 1);
	}
	else {
		resizeString(username, username.size() - 1);
	}
}

void NameInputUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(backgroudShape, states);
	for (int i = 0; i < nameLenth; i++) {
		// txt drawing
		target.draw(txts[i], states);

		// rectangle drawing
		target.draw(rects[i], states);
	}
	target.draw(inform, states);
}