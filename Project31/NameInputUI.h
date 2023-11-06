#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class NameInputUI : sf::Drawable
{
public:
	NameInputUI(int x, int y, int offset, int current_char = 0, int current_size = 50, std::string username);
	void setChar(int index, bool upOrDown);

private:
	// position and scale
	int x_position;
	int y_position;
	int x_offset;

	// char info
	char current_chracter;
	int character_size;

	// name string info
	const int nameLenth = 5;;
	std::string username;

	//drawable objs
	sf::Text txts[5];
	sf::Font font;

	sf::RectangleShape rects[5];
	
	// drawing func
	void draw(sf::RenderTarget& target, sf::RenderStates states);
};

