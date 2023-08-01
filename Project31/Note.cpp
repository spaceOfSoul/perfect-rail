#include "Note.h"
void Note::draw(float dt) {
    sf::RectangleShape shape(sf::Vector2f(size, size));
    shape.setPosition(position);
    shape.setFillColor(color);
    window.draw(shape);
}
