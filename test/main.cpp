#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Text text("Hello SFML", font, 50);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Sounds/sound.ogg")) {
        std::cerr << "Error loading sound\n";
        return 1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
