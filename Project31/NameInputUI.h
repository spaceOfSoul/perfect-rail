#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class NameInputUI : sf::Drawable
{
public:
	NameInputUI();
	void setChar(int index, bool upOrDown);

private:
	char current_chracter;
	const int nameLenth = 5;
	std::string username;
	sf::Text txt[5];
	sf::RectangleShape rect[5];

	void draw(sf::RenderTarget& target, sf::RenderStates states);
};

