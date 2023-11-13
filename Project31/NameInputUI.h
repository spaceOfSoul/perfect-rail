#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class NameInputUI : public sf::Drawable
{
public:
	NameInputUI(int x, int y, int offset, int width, int height, int current_chracter = 0, int current_size = 50);
	void setChar(bool upOrDown);
	void setIndex(bool upOrDown);
	void initInput();
	std::string getUserName();

private:
	// position and scale
	int x_position;
	int y_position;
	int x_offset;

	// char info
	uint8_t character_size;

	char current_chracter;
	//uint8_t current_size;
	uint8_t index;

	// name string info
	const int nameLenth = 5;;
	std::string username;

	//drawable objs
	sf::Text txts[5];
	sf::Font font;

	sf::Text inform;

	sf::RectangleShape rects[5];

	sf::RectangleShape backgroudShape; // background
	
	// drawing func
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

