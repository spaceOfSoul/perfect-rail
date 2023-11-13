#include "deadPannel.h"

DeadPannel::DeadPannel(float x, float y) {
	this->x = x;
	this->y = y;

	height = 600;
	width = 800;

	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("��Ʈ�� ����!");
	}

	resgionShaape.setPosition(0,0);
	resgionShaape.setSize(sf::Vector2f(width, height));
	resgionShaape.setFillColor(sf::Color(125, 0, 0, 125));

	main_text.setFont(font);
	main_text.setFillColor(sf::Color::White);
	main_text.setCharacterSize(50); // font size 50, pos (200, 350)
	main_text.setString("GAME OVER");

	sub_text.setFont(font);
	sub_text.setFillColor(sf::Color::White);
	sub_text.setCharacterSize(38); // font size 50, pos (200, 350)
	sub_text.setString("U NEED MORE PRACTICE");


	// �ؽ�Ʈ �߾�����
	sf::FloatRect textRect = main_text.getLocalBounds();
	main_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	main_text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 30));

	// sub_text ��ġ ���� (main_text �Ʒ��� ��ġ)
	textRect = sub_text.getLocalBounds();
	sub_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	// sub_text�� main_text �ٷ� �Ʒ��� ��ġ��Ű��
	sub_text.setPosition(sf::Vector2f(width / 2.0f, main_text.getPosition().y + 60));
}

void DeadPannel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(resgionShaape, states);
	target.draw(main_text, states);
	target.draw(sub_text, states);
}

