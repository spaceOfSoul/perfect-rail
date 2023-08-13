#include "OptionScene.h"
#include <sstream>

OptionScene::OptionScene(float width, float height) : am(AudioManager::Instance()), sm(SettingsManager::Instance()) {
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음\n");
	}

	// render texts
	titleText.setFont(font);
	titleText.setString("Options");
	titleText.setCharacterSize(fontSize);
	titleText.setPosition(sf::Vector2f(200.f, 50.f));
	titleText.setFillColor(sf::Color::White);

	for (int i = 0; i < OPTION_ITEM; ++i) {
		menus[i].setFont(font);
		menus[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
		menus[i].setCharacterSize(fontSize);
		menus[i].setPosition(sf::Vector2f(width / 2, height / (OPTION_ITEM + 1) * (i + 1)));
	}

	selectedItemIndex = 0;
}

OptionScene::~OptionScene()
{
}

void OptionScene::onActivate() {
	std::stringstream ss;

	ss << "Music Volume: " << (int)sm.GetMusicVolume();
	menus[0].setString(ss.str());
	ss.str("");
	ss.clear();

	ss << "Sound Volume: " << (int)sm.GetSoundVolume();
	menus[1].setString(ss.str());
	ss.str("");
	ss.clear();

	ss << "Note Speed: " << (int)sm.GetNoteSpeed();
	menus[2].setString(ss.str());
	ss.str("");
	ss.clear();

	menus[3].setString("Exit");
}

void OptionScene::onDeactivate() {
	sm.saveOption();
}

void OptionScene::draw(sf::RenderWindow& window) {
	window.draw(titleText);
	for (int i = 0; i < OPTION_ITEM; i++)
	{
		window.draw(menus[i]);
	}
}

void OptionScene::update(float dt) {

}

void OptionScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		am.PlayEventSound("menu_select");
		menus[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menus[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void OptionScene::MoveDown()
{
	if (selectedItemIndex + 1 < OPTION_ITEM)
	{
		am.PlayEventSound("menu_select");
		menus[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menus[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void OptionScene::MoveLeft() {
	std::stringstream ss;
	if (selectedItemIndex == 0) { // music volume
		float vol = sm.GetMusicVolume();
		if (vol >= 10) 
			vol -= 10;
		sm.SetMusicVolume(vol);
		am.PlayEventSound("menu_select");

		ss << "Music Volume: " << (int)sm.GetMusicVolume();
		menus[0].setString(ss.str());
		ss.str("");
		ss.clear();
	}
	else if (selectedItemIndex == 1) { // sound volume
		float vol = sm.GetSoundVolume();
		if (vol >= 10)
			vol -= 10;
		sm.SetSoundVolume(vol);
		am.PlayEventSound("menu_select");

		ss << "Sound Volume: " << (int)sm.GetSoundVolume();
		menus[1].setString(ss.str());
		ss.str("");
		ss.clear();
	}
	else if (selectedItemIndex == 2) { // note speed
		double speed = sm.GetNoteSpeed();
		if (speed >= 300)
			speed -= 50;
		sm.SetNoteSpeed(speed);
		am.PlayEventSound("menu_select");

		ss << "Note Speed: " << (int)sm.GetNoteSpeed();
		menus[2].setString(ss.str());
		ss.str("");
		ss.clear();
	}
}

void OptionScene::MoveRight() {
	std::stringstream ss;
	if (selectedItemIndex == 0) { // music volume
		float vol = sm.GetMusicVolume();
		if (vol <= 90)
			vol += 10;
		sm.SetMusicVolume(vol);
		am.PlayEventSound("menu_select");

		ss << "Music Volume: " << (int)sm.GetMusicVolume();
		menus[0].setString(ss.str());
		ss.str("");
		ss.clear();
	}
	else if (selectedItemIndex == 1) { // sound volume
		float vol = sm.GetSoundVolume();
		if (vol <= 90)
			vol += 10;
		sm.SetSoundVolume(vol);
		am.PlayEventSound("menu_select");

		ss << "Sound Volume: " << (int)sm.GetSoundVolume();
		menus[1].setString(ss.str());
		ss.str("");
		ss.clear();
	}
	else if (selectedItemIndex == 2) { // note speed
		double speed = sm.GetNoteSpeed();
		if (speed <= 2950)
			speed += 50;
		sm.SetNoteSpeed(speed);
		am.PlayEventSound("menu_select");

		ss << "Note Speed: " << (int)sm.GetNoteSpeed();
		menus[2].setString(ss.str());
		ss.str("");
		ss.clear();
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
		else if (event.key.code == sf::Keyboard::Left) {
			MoveLeft();
		}
		else if (event.key.code == sf::Keyboard::Right) {
			MoveRight();
		}
		else if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
		{
			onDeactivate();
			return Signal::GoToMainMenu;
		}
	}
	return Signal::None;
}
