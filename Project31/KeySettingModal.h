#pragma once
#include <SFML/Graphics.hpp>

class KeySettingModal : public sf::Drawable
{
public:
    KeySettingModal(float x, float y, float width, float height);
    void setKey(uint8_t index, char keys);
    void setAllkey(char *);
    void setKeyCursor(uint8_t index);
    void setKeyReady();
private:
    sf::RectangleShape OuterRect;
    sf::RectangleShape innerRect;
    const uint8_t margin = 6;

    // key UI
    sf::RectangleShape keyRect[4];
    sf::ConvexShape cursur; // 아래 위 삼각형
    const int keyRect_padding = 60;
    float cur_size = 20;

    sf::Text keyText[4];

    sf::Font font;

    // keys
    char keys[4];
    uint8_t select_index;

    // modal state
    bool is_ready;

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

