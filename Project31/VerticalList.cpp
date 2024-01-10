#include "VerticalList.h"

VerticalList::VerticalList(float width, float height) {
	this->width = width;
	this->height = height;
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음.\n");
	}

	currentIndex = 0;

	for (uint8_t i = 0; i < MAX_NUM; i++) {
		textItems[i].setFont(font);
		textItems[i].setString("");
		textItems[i].setPosition(sf::Vector2f((width / 2) + pos_x, (height / (MAX_NUM + 1) * (i + 1)) + pos_y));

		if (i == currentIndex) { // 선택된 곡은 붉은 색으로 (추후에 RectangleShape 추가)
			textItems[i].setFillColor(sf::Color::Red);
		}
		else {
			textItems[i].setFillColor(sf::Color::White);
		}
	}
}

void VerticalList::addItem(const std::string& item) {
	items.push_back(item);
	// 아이템 추가 시 endIndex 업데이트
	updateIndex();
}

void VerticalList::MoveDown() {
	currentIndex = (currentIndex + 1) % items.size();
	updateIndex();
}

void VerticalList::MoveUp() {
	currentIndex = (currentIndex - 1 + items.size()) % items.size();
	updateIndex();
}

void VerticalList::updateIndex() {
	// startIndex와 endIndex 업데이트
	startIndex = (currentIndex - MAX_NUM / 2 + items.size()) % items.size();
	endIndex = (startIndex + MAX_NUM - 1) % items.size();
}

void VerticalList::draw(sf::RenderWindow& window) {
	int itemCount = items.size();
	for (int i = 0; i < MAX_NUM; i++) {
		int itemIndex = (startIndex + i) % itemCount;
		textItems[i].setString(items[itemIndex]);

		//거리
		int forward;
		int backward;

		if (itemIndex >= currentIndex) 
			forward= itemIndex - currentIndex;
		else 
			forward = itemIndex + itemCount - currentIndex;
		
		if (currentIndex >= itemIndex)
			backward = currentIndex - itemIndex;
		else
			backward = currentIndex + itemCount - itemIndex;

		int distance = std::min(forward, backward);

		if (itemIndex == currentIndex) {
			textItems[i].setFillColor(sf::Color::Red); // selected
		}
		else if (distance == 1) {
			textItems[i].setFillColor(sf::Color::White); // 선택된 항목의 바로 위/아래
		}
		else {
			// 회색 표시
			int greyValue = 255 - distance * (255 / (MAX_NUM / 2));
			textItems[i].setFillColor(sf::Color(greyValue, greyValue, greyValue));
		}

		window.draw(textItems[i]);
	}
}


void VerticalList::setPos(float x,float y) {
	this->pos_x = x;
	this->pos_y = y;
	for (uint8_t i = 0; i < MAX_NUM; i++) {
		textItems[i].setPosition(sf::Vector2f((width / 2) + pos_x, (height / (MAX_NUM + 1) * (i + 1)) + pos_y));
	}
}

int VerticalList::getCurrentIndex() {
	return currentIndex;
}