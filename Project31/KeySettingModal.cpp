#include "KeySettingModal.h"

KeySettingModal::KeySettingModal(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;

	this->height = height;
	this->width = width;

	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음!");
	}

	this->blink_timer = 0;

	OuterRect.setFillColor(sf::Color(80,80,80));
	OuterRect.setSize(sf::Vector2f(width, height));
	OuterRect.setPosition(x,y);

	innerRect.setFillColor(sf::Color(120, 120, 120));
	innerRect.setSize(sf::Vector2f(width - 2*margin, height - 2*margin));
	innerRect.setPosition(x+margin, y + margin);

	Title.setFont(font);
	Title.setCharacterSize(65);
	Title.setFillColor(sf::Color::White);
	Title.setPosition(x,y - 85);
	Title.setString("Key Setting");

	for (int i = 0; i < 4; i++) {
		this->keyRect[i].setFillColor(sf::Color(60, 60, 60));
		this->keyRect[i].setSize(sf::Vector2f(80, 80)); // size(:100) - keyRect_padding*2
		this->keyRect[i].setPosition(x + 100 * i + keyRect_padding, y + 75);
		
		this->keyText[i].setFont(font);
		this->keyText[i].setCharacterSize(65);
		this->keyText[i].setFillColor(sf::Color::White);
		this->keyText[i].setPosition(x + 100 * i + keyRect_padding+15, y + 72);
		this->keyText[i].setString("D");
	}

	// cursur init
	// point ea
	cursur.setPointCount(3);

	float cur_size = 20;  // 삼각형의 크기
	float triangleX = this->keyRect[0].getPosition().x + (this->keyRect[0].getSize().x - cur_size) / 2;
	float triangleY = this->keyRect[0].getPosition().y + this->keyRect[0].getSize().y + (cur_size/2);
	cursur.setPosition(triangleX, triangleY);
	cursur.setPoint(0, sf::Vector2f(cur_size / 2, 0));
	cursur.setPoint(1, sf::Vector2f(0, cur_size));
	cursur.setPoint(2, sf::Vector2f(cur_size, cur_size));
	cursur.setFillColor(sf::Color::White);

	// 선택한 키 인덱스
	select_index = -1;
}

void KeySettingModal::setKey(uint8_t index, char keys) {
	this->keys[index] = keys;
	this->keyText[index].setString(keys);
}

void KeySettingModal::setAllkey(char* keys) {
	for (uint8_t i = 0; i < 4; i++) {
		this->keys[i] = keys[i];
		this->keyText[i].setString(keys[i]);
	}
}

void KeySettingModal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(OuterRect, states);
	target.draw(innerRect, states);
	for (int i = 0; i < 4; i++) {
		target.draw(keyRect[i], states);
		target.draw(keyText[i], states);
	}
	target.draw(Title, states);
	target.draw(cursur, states);
}