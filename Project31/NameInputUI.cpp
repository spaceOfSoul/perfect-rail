#include "NameInputUI.h"

NameInputUI::NameInputUI(int x, int y, int offset,int width, int height, int current_chracter, int current_size) {
	this->x_position = x;
	this->y_position = y;
	this->x_offset = offset;
	this->current_chracter = current_chracter;
	this->character_size = current_size;

	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음!");
	}

	for (int i = 0; i < nameLenth; i++) {
		// txt setting
		txts[i].setFont(font);
		txts[i].setFillColor(sf::Color::White);
		txts[i].setCharacterSize(character_size);

		// rectangle setting
		rects[i].setFillColor(sf::Color::White);
		rects[i].setPosition(sf::Vector2f(x_offset*100, y_position + character_size/2));
		rects[i].setSize(sf::Vector2f(character_size, character_size/2));
	}

	backgroudShape.setFillColor(sf::Color(125, 125, 125, 125)); // r,g,b,a
	backgroudShape.setPosition(sf::Vector2f(0, 0));
	backgroudShape.setSize(sf::Vector2f(width, height));
}

void NameInputUI::setChar(bool upOrDown) { // 문자 업다운

}

void NameInputUI::setIndex(bool upOrDown){

}

void NameInputUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(backgroudShape, states);
	for (int i = 0; i < nameLenth; i++) {
		// txt drawing
		target.draw(txts[i], states);

		// rectangle drawing
		target.draw(rects[i], states);
	}
}