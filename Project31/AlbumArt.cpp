#include "AlbumArt.h"

AlbumArt::AlbumArt(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& texturePath) {
    rectangle.setSize(size);
    rectangle.setPosition(position);

    imSize = size;
    pos = position;

    if (!texture.loadFromFile(texturePath)) {
        printf("texture loading error\n");
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);

    sf::Vector2u textureSize = texture.getSize();
    float scaleX = size.x / (float)(textureSize.x);
    float scaleY = size.y / (float)(textureSize.y);
    sprite.setScale(scaleX, scaleY);
}

void AlbumArt::draw(sf::RenderWindow& window) const {
    window.draw(rectangle);
    window.draw(sprite);
}

void AlbumArt::setTexturePath(const std::string& path) {
    if (!texture.loadFromFile(path)) {
        printf("album image loading error\n");
    }
    else {
        sprite.setTexture(texture);
        sprite.setPosition(pos);

        sf::Vector2u textureSize = texture.getSize();
        float scaleX = imSize.x / (float)(textureSize.x);
        float scaleY = imSize.y / (float)(textureSize.y);

        sprite.setScale(scaleX, scaleY);
    }
}