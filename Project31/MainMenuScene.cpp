#include "MainMenuScene.h"
#include <stdio.h>

MainMenuScene::MainMenuScene() {
    if (!font.loadFromFile("fonts\\arial.ttf")) {
        printf("��Ʈ�� ����\n");
    }

    titleText.setFont(font);
    titleText.setString("Main Menu");
    titleText.setCharacterSize(24);
    titleText.setPosition(sf::Vector2f(200.f, 50.f));
    titleText.setFillColor(sf::Color::White);

    startButton.setSize(sf::Vector2f(200.f, 50.f));
    startButton.setPosition(sf::Vector2f(200.f, 200.f));
    startButton.setFillColor(sf::Color::Red);

    buttonText.setFont(font);
    buttonText.setString("Game Start");
    buttonText.setCharacterSize(24);
    buttonText.setPosition(startButton.getPosition() + sf::Vector2f(75.f, 10.f));
    buttonText.setFillColor(sf::Color::White);
}

void MainMenuScene::update(float dt) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();
    if (startButton.getGlobalBounds().contains(mousePos)) {
        startButton.setFillColor(sf::Color::Green);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {// ���ӽ��۹�ư
            printf("���۹�ư�� ����\n");
        }
    }
    else {
        startButton.setFillColor(sf::Color::Red);
    }
}

void MainMenuScene::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(startButton);
    window.draw(buttonText);
}
