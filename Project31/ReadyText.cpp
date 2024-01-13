#include "ReadyText.h"
#include <string>
ReadyText::ReadyText(float xPos, float yPos, float initSize, sf::Font font) : scale(1.0f)
{
    width = initSize;
    height = initSize;
    pos = sf::Vector2f(xPos, yPos);
    this-> font = font;
    circle.setPosition(pos);
    circle.setRadius(initSize);
    
    fontSize = initSize;
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setString("3");

    float centerX_number = pos.x - text.getLocalBounds().width / 2.0f;
    float centerY_number = pos.y - text.getLocalBounds().height / 2.0f;
    text.setPosition(centerX_number, centerY_number);

    scale = 1.f;
}

void ReadyText::setPosition(float x, float y) {
    pos.x = x;
    pos.y = y;
}

void ReadyText::setFont(sf::Font& font) {
    this->font = font;
    text.setFont(font);
}

void ReadyText::setCount(uint8_t count) {
    if (count == 3)
        text.setString("Go!");
    else 
        text.setString(std::to_string(3-count));
    

    scale = 1.3f;
    text.setCharacterSize((int)(fontSize * scale));
    //printf("font size : %d\n", (int)(fontSize * scale));

    float centerX_number = pos.x - text.getLocalBounds().width / 2.0f;
    //float centerY_number = pos.y - text.getLocalBounds().height / 2.0f;
    text.setPosition(centerX_number, pos.y);
}


void ReadyText::update(float dt) {
    scale -= 3.f * dt;
    if (scale <= 1.0f) {
        scale = 1.0f;
    }
    text.setCharacterSize((int)(fontSize * scale));

    float centerX_number = pos.x - text.getLocalBounds().width / 2.0f;
    //float centerY_number = pos.y - text.getLocalBounds().height / 2.0f;
    text.setPosition(centerX_number, pos.y);
}

void ReadyText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text, states);
}

