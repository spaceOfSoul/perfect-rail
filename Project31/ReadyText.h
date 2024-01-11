#pragma once
#include <SFML/Graphics.hpp>

class ReadyText : public sf::Drawable
{
private:
	float width, height;
	sf::Vector2f pos;
	sf::CircleShape circle;
	sf::Text text;
	sf::Font font;
	float scale;
	uint8_t fontSize;

public:
	ReadyText(float xPos, float yPos, float initSize, sf::Font font);
	void update(float dt);
	void setCount();
	void setFont(sf::Font&);
	void setPosition(float x, float y);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

