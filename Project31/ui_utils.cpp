#include "ui_utils.h"

void fadeOutText(sf::Text& text, float dt, float fadeSpeed) {
    sf::Color color = text.getFillColor();

    int newAlpha = (int)(color.a - fadeSpeed * dt);

    if (newAlpha < 0) {
        newAlpha = 0;
    }

    color.a = (sf::Uint8)(newAlpha);
    text.setFillColor(color);
}
