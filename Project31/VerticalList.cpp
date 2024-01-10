#include "VerticalList.h"

VerticalList::VerticalList(float width, float height) {
	this->width = width;
	this->height = height;
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("��Ʈ�� ����.\n");
	}

	currentIndex = 0;

	for (uint8_t i = 0; i < MAX_NUM; i++) {
		textItems[i].setFont(font);
		textItems[i].setString("");
		textItems[i].setPosition(sf::Vector2f((width / 2) + pos_x, (height / (MAX_NUM + 1) * (i + 1)) + pos_y));

		if (i == currentIndex) { // ���õ� ���� ���� ������ (���Ŀ� RectangleShape �߰�)
			textItems[i].setFillColor(sf::Color::Red);
		}
		else {
			textItems[i].setFillColor(sf::Color::White);
		}
	}
}

void VerticalList::addItem(const std::string& item) {
	items.push_back(item);
	// ������ �߰� �� endIndex ������Ʈ
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
	// startIndex�� endIndex ������Ʈ
	startIndex = (currentIndex - MAX_NUM / 2 + items.size()) % items.size();
	endIndex = (startIndex + MAX_NUM - 1) % items.size();
}

void VerticalList::draw(sf::RenderWindow& window) {
	int itemCount = items.size();
	for (int i = 0; i < MAX_NUM; i++) {
		int itemIndex = (startIndex + i) % itemCount;
		textItems[i].setString(items[itemIndex]);

		//�Ÿ�
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
			textItems[i].setFillColor(sf::Color::White); // ���õ� �׸��� �ٷ� ��/�Ʒ�
		}
		else {
			// ȸ�� ǥ��
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