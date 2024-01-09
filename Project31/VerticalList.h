#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "AudioManager.h"

#define MAX_NUM 16

class VerticalList {
public:
    VerticalList(float width, float height);
    void addItem(const std::string& item);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    void updateIndex();

    int getCurrentIndex();
private:

    int startIndex;
    int endIndex;
    int currentIndex;

    std::vector<std::string> items;
    sf::Text textItems[MAX_NUM];
    int selectedItemIndex;
    float width, height;
    sf::Font font;
};