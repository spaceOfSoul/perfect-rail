#include "MainMenuScene.h"

#include <iostream>

MainMenuScene::MainMenuScene(float width, float height, sf::Font& font) : am(AudioManager::Instance()), font(font) {
	this->width = width;
	this->height = height;

	selectedItemIndex = 0;

	// hidden command (for test)
	testSceneCommands = { sf::Keyboard::R, sf::Keyboard::T, sf::Keyboard::R, sf::Keyboard::T};
	hiddenSceneActivate = false;

	for (int i = 0; i < 3; i++) {
		if (!cat_texture[i].loadFromFile(cat_path[i]))
			printf("Cat texture %d load failed\n", i);
		printf("%s load.\n", cat_path[i].c_str());
	}
	cat.setTexture(cat_texture[0]);
	cat.setScale(0.2f, 0.2f);
	cat.setPosition(100, 250);

	leftPaw.setTexture(cat_texture[1]);
	leftPaw.setScale(0.2f, 0.2f);
	leftPaw.setPosition(100, 250);

	rightPaw.setTexture(cat_texture[2]);
	rightPaw.setScale(0.2f, 0.2f);
	rightPaw.setPosition(100, 250);
}

bool MainMenuScene::checkForHiddenCommand(sf::Keyboard::Key keyPressed) {
	currentInputSequence.push_back(keyPressed);

	while (currentInputSequence.size() > testSceneCommands.size() ||
		!std::equal(currentInputSequence.begin(), currentInputSequence.end(), testSceneCommands.begin())) {
		currentInputSequence.erase(currentInputSequence.begin());
	}

	if (currentInputSequence == testSceneCommands) {
		return true;
	}
	return false;
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
	window.draw(cat);
	window.draw(leftPaw);
	window.draw(rightPaw);
	window.draw(blackLine);
}

void MainMenuScene::MoveUp()
{
	//printf("up %d \n", selectedItemIndex);

	if (selectedItemIndex > 0)
	{
		am.PlayEventSound("menu_select");
		menu_texts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		//printf("%d to %d \n", selectedItemIndex + 1, selectedItemIndex);

		menu_texts[selectedItemIndex].setFillColor(sf::Color::Red);
	}

	//printf("up %d \n", selectedItemIndex);
}

void MainMenuScene::MoveDown()
{
	//printf("down %d \n", selectedItemIndex);

	if (selectedItemIndex < MAX_OF_ITEM-1)
	{
		am.PlayEventSound("menu_select");
		menu_texts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		//printf("%d \n", selectedItemIndex);
		menu_texts[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	//printf("down %d \n", selectedItemIndex);
}

Signal MainMenuScene::handleInput(sf::Event event, sf::RenderWindow &window) {
	if (event.type == sf::Event::KeyPressed)
	{
		hiddenSceneActivate = checkForHiddenCommand(event.key.code);

		if (hiddenSceneActivate)
			return Signal::DebugCommandActivated;
		
		// menu select
		if (event.key.code == sf::Keyboard::Up)
		{
			MoveUp();
			return Signal::None;
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			MoveDown();
			return Signal::None;
		}
		else if (event.key.code == sf::Keyboard::Return)
		{

			if (selectedItemIndex == 0)
			{
				//printf("Play button has been pressed\n");
				return Signal::GoToSongMenu;
				
			}
			else if (selectedItemIndex == 1)
			{
				//printf("Option button has been pressed\n");
				return Signal::GoToOptionMenu;
			}
			else if (selectedItemIndex == 2) // not working now
			{
				 //window.close();
				std::cerr << "pushed";
			}
			return Signal::None;
		}
	}
	return Signal::None;
}

void MainMenuScene::update(float dt) {
	// ±¸ÇöºÎ
}

void MainMenuScene::onActivate() {
	// render texts
	titleText.setFont(font);
	titleText.setString("Perfect Rail");
	titleText.setCharacterSize(fontSize * 1.5);
	titleText.setPosition(sf::Vector2f(100.f, 150.f));
	titleText.setFillColor(sf::Color::White);

	blackLine.setFillColor(sf::Color::Black);
	blackLine.setSize(sf::Vector2f(50,200));
	blackLine.setPosition(sf::Vector2f(290, 200));

	/*menu_texts[2].setFont(font);
	menu_texts[2].setFillColor(sf::Color::White);
	menu_texts[2].setString("Test");
	menu_texts[2].setCharacterSize(fontSize);
	menu_texts[2].setPosition(sf::Vector2f(width / 2, height / (MAX_OF_ITEM + 1) * 3));*/

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

	selectedItemIndex = 0;
}

void MainMenuScene::onDeactivate() {

}
