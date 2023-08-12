#include "OptionScene.h"
OptionScene::OptionScene(float width, float height) : am(AudioManager::Instance()) {
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음\n");
	}

	// render texts
	titleText.setFont(font);
	titleText.setString("Options");
	titleText.setCharacterSize(fontSize);
	titleText.setPosition(sf::Vector2f(200.f, 50.f));
	titleText.setFillColor(sf::Color::White);

	menus[0].setFont(font);
	menus[0].setFillColor(sf::Color::Red);
	menus[0].setString("Music Volume");
	menus[0].setCharacterSize(fontSize);
	menus[0].setPosition(sf::Vector2f(width / 2, height / (OPTION_ITEM + 1) * 1));

	menus[1].setFont(font);
	menus[1].setFillColor(sf::Color::White);
	menus[1].setString("Sound Volume");
	menus[1].setCharacterSize(fontSize);
	menus[1].setPosition(sf::Vector2f(width / 2, height / (OPTION_ITEM + 1) * 2));

	menus[2].setFont(font);
	menus[2].setFillColor(sf::Color::White);
	menus[2].setString("Note Speed");
	menus[2].setCharacterSize(fontSize);
	menus[2].setPosition(sf::Vector2f(width / 2, height / (OPTION_ITEM + 1) * 3));

	menus[3].setFont(font);
	menus[3].setFillColor(sf::Color::White);
	menus[3].setString("Exit");
	menus[3].setCharacterSize(fontSize);
	menus[3].setPosition(sf::Vector2f(width / 2, height / (OPTION_ITEM + 1) * 3));

	selectedItemIndex = 0;
}

OptionScene::~OptionScene()
{
}

void OptionScene::onActivate() {

}

void OptionScene::onDeactivate() {

}

void OptionScene::draw(sf::RenderWindow& window) {
	window.draw(titleText);
	for (int i = 0; i < OPTION_ITEM; i++)
	{
		window.draw(menus[i]);
	}
}

void OptionScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		am.PlaySound("menu_select");
		menus[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menus[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void OptionScene::MoveDown()
{
	if (selectedItemIndex + 1 < OPTION_ITEM)
	{
		am.PlaySound("menu_select");
		menus[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menus[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

Signal OptionScene::handleInput(sf::Event event, sf::RenderWindow& window) {
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
		else if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
		{
			onDeactivate();
			return Signal::GoToMainMenu;
		}
	}
	return Signal::None;
}
