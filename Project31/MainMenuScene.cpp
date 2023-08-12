#include "MainMenuScene.h"

#include <stdio.h>

MainMenuScene::MainMenuScene(float width, float height) : am(AudioManager::Instance()) {
    if (!font.loadFromFile("fonts\\arial.ttf")) {
        printf("폰트가 없음\n");
    }

	// render texts
	titleText.setFont(font);
	titleText.setString("Main Menu");
	titleText.setCharacterSize(fontSize);
	titleText.setPosition(sf::Vector2f(200.f, 50.f));
	titleText.setFillColor(sf::Color::White);

	menu_texts[0].setFont(font);
	menu_texts[0].setFillColor(sf::Color::Red);
	menu_texts[0].setString("Play");
	menu_texts[0].setCharacterSize(fontSize);
	menu_texts[0].setPosition(sf::Vector2f(width / 2, height / (MAX_OF_ITEM + 1) * 1));

	menu_texts[1].setFont(font);
	menu_texts[1].setFillColor(sf::Color::White);
	menu_texts[1].setString("Options");
	menu_texts[1].setCharacterSize(fontSize);
	menu_texts[1].setPosition(sf::Vector2f(width / 2, height / (MAX_OF_ITEM + 1) * 2));

	menu_texts[2].setFont(font);
	menu_texts[2].setFillColor(sf::Color::White);
	menu_texts[2].setString("Exit");
	menu_texts[2].setCharacterSize(fontSize);
	menu_texts[2].setPosition(sf::Vector2f(width / 2, height / (MAX_OF_ITEM + 1) * 3));

	selectedItemIndex = 0;
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::draw(sf::RenderWindow& window) {
    window.draw(titleText);
	for (int i = 0; i < MAX_OF_ITEM; i++)
	{
		window.draw(menu_texts[i]);
	}
}

void MainMenuScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		am.PlaySound("menu_select");
		menu_texts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu_texts[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MainMenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_OF_ITEM)
	{
		am.PlaySound("menu_select");
		menu_texts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu_texts[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

Signal MainMenuScene::handleInput(sf::Event event, sf::RenderWindow &window) {
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			MoveUp();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			MoveDown();
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			int pressedItem = GetPressedItem();

			if (pressedItem == 0)
			{
				printf("Play button has been pressed\n");
				return Signal::GoToSongMenu;
				
			}
			else if (pressedItem == 1)
			{
				printf("Option button has been pressed\n");
				return Signal::GoToOptionMenu;
			}
			else if (pressedItem == 2)
			{
				window.close();
			}
		}
	}
}

void MainMenuScene::update(float dt) {
	// 구현부
}

void MainMenuScene::onActivate() {

}

void MainMenuScene::onDeactivate() {

}
