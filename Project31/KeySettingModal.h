#pragma once
#include <SFML/Graphics.hpp>

class KeySettingModal : public sf::Drawable
{
public:
    KeySettingModal(float x, float y, float width, float height);
    void setKey(char* keys);
private:
    sf::RectangleShape OuterRect;
    sf::RectangleShape innerRect;
    const uint8_t margin = 6;

    sf::RectangleShape keyRect[4];
    sf::ConvexShape cursur; // 아래위 삼각형
    char keys[4];
    const int keyRect_padding = 60;

    sf::Text keyText[4];

    sf::Font font;

    sf::Text Title;

    float x, y; // pos
    float height, width;
    // for animation
    float blink_timer;

    // animation function
    void blink(float dt);

    // draw
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

