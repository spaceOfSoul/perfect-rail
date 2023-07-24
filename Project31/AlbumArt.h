#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>

class AlbumArt {
public:
    AlbumArt(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& texturePath);

    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape rectangle;
    sf::Texture texture;
    sf::Sprite sprite;
};
