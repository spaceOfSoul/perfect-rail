#include "OptionScene.h"
#include <sstream>

OptionScene::OptionScene(float width, float height, sf::Font& font) : 
	am(AudioManager::Instance()),
	sm(SettingsManager::Instance()),
	key_setUI(150, 175, 500, 250),
	font(font) {
	this->width = width;
	this->height = height;

	backStageOverlay.setSize(sf::Vector2f(width, height));
	backStageOverlay.setFillColor(sf::Color(0, 0, 0, 128));
	backStageOverlay.setPosition(0, 0);

	selectedItemIndex = 0;
}

OptionScene::~OptionScene()
{
}

void OptionScene::onActivate() {
	selectedItemIndex = 0;
	isWaitForKey = false;
	isKeySetMode = false;

	for (int i = 0; i < 4; i++) {
		key_setUI.setKey(i, KeyToString(sm.GetKey(i)));
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

	std::stringstream ss;

	ss << "Music Volume: " << (int)sm.GetMusicVolume() << "%";
	menus[0].setString(ss.str());
	ss.str("");
	ss.clear();

	ss << "Sound Volume: " << (int)sm.GetSoundVolume() << "%";
	menus[1].setString(ss.str());
	ss.str("");
	ss.clear();

	ss << "Note Speed: " << (int)sm.GetNoteSpeed();
	menus[2].setString(ss.str());
	ss.str("");
	ss.clear();

	ss << "judgeline Y: " << (int)sm.GetJudgeLine_Y();
	menus[3].setString(ss.str());
	ss.str("");
	ss.clear();

	ss << "Time Sync: " << (int)sm.GetTimeSync() << "ms";
	menus[4].setString(ss.str());
	ss.str("");
	ss.clear();

	ss << "Key binding";
	menus[5].setString(ss.str());
	ss.str("");
	ss.clear();

	menus[6].setString("Exit");
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

	if (isKeySetMode) {
		window.draw(backStageOverlay);
		window.draw(key_setUI);
	}
}

void OptionScene::update(float dt) {
	if (isKeySetMode && isWaitForKey) {
		key_setUI.blink(dt);
	}
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

		ss << "Music Volume: " << (int)sm.GetMusicVolume() << "%";
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

		ss << "Sound Volume: " << (int)sm.GetSoundVolume() << "%";
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
	else if (selectedItemIndex == 3) { // jedgeline y position
		int y = sm.GetJudgeLine_Y();
		if (y >= -20)
			y -= 5;
		sm.SetJudgeLine_Y(y);
		am.PlayEventSound("menu_select");

		ss << "judgeline Y: " << (int)sm.GetJudgeLine_Y();
		menus[3].setString(ss.str());
		ss.str("");
		ss.clear();
	}
	else if (selectedItemIndex == 4) { // time sync
		int sync = sm.GetTimeSync();
		if (sync >= -999)
			sync -= 1;

		sm.SetTimeSync(sync);
		am.PlayEventSound("menu_select");

		ss << "Time Sync: " << (int)sm.GetTimeSync() << "ms";
		menus[4].setString(ss.str());
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

		ss << "Music Volume: " << (int)sm.GetMusicVolume() << "%";
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

		ss << "Sound Volume: " << (int)sm.GetSoundVolume() << "%";
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
	else if (selectedItemIndex == 3) { // judgeline y position
		int y = sm.GetJudgeLine_Y();
		if (y <= 295)
			y += 5;
		sm.SetJudgeLine_Y(y);
		am.PlayEventSound("menu_select");

		ss << "judgeline Y: " << sm.GetJudgeLine_Y();
		menus[3].setString(ss.str());
		ss.str("");
		ss.clear();
	}
	else if (selectedItemIndex == 4) { // time sync
		int sync = sm.GetTimeSync();
		if (sync <= 999)
			sync += 1;

		sm.SetTimeSync(sync);
		am.PlayEventSound("menu_select");

		ss << "Time Sync: " << (int)sm.GetTimeSync() << "ms";
		menus[4].setString(ss.str());
		ss.str("");
		ss.clear();
	}
}

Signal OptionScene::handleInput(sf::Event event, sf::RenderWindow& window) {
	if (event.type == sf::Event::KeyPressed)
	{
		// key set mode
		if (isKeySetMode) {
			if (isKeySetMode) {
				if (!isWaitForKey) {
					if (event.key.code == sf::Keyboard::Left) {
						selectedKeyIndex = (selectedKeyIndex + 3) % 4;
						key_setUI.setKeyCursor(selectedKeyIndex);
						printf("selected %d.\n", selectedKeyIndex);
					}
					else if (event.key.code == sf::Keyboard::Right) {
						selectedKeyIndex = (selectedKeyIndex + 1) % 4; 
						key_setUI.setKeyCursor(selectedKeyIndex);
						printf("selected %d.\n", selectedKeyIndex);
					}
					else if (event.key.code == sf::Keyboard::Enter) {
						isWaitForKey = true;
						printf("waiting for new key for %d.\n", selectedKeyIndex);
					}
					else if (event.key.code == sf::Keyboard::Escape) {
						isKeySetMode = false;
						printf("exited key set mode.\n");
					}
				}
				else { // 엔터 눌러서 대기에 온 후
					if (selectedKeyIndex >= 0 && selectedKeyIndex < 4) {
						sf::Keyboard::Key newKey = event.key.code; // 현재 입력된 키
						sm.SetKey(selectedKeyIndex, newKey);

						sm.SetKey(selectedKeyIndex, newKey);
						key_setUI.setKey(selectedKeyIndex, KeyToString(newKey));
						printf("key %d set to %s\n", selectedKeyIndex, KeyToString(newKey).c_str());

						isWaitForKey = false;
					}
					else {
						printf("Invalid key index %d.\n", selectedKeyIndex); // 요기로 가는 일은 없어야함.
					}
				}
			}

		}
		else { // is not key set mode (general option)
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
			else if (event.key.code == sf::Keyboard::Escape)
			{
				onDeactivate();
				return Signal::GoToMainMenu;
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				if (selectedItemIndex == 5) {
					printf("key binding is pushed.\n");
					isKeySetMode = true;
					selectedKeyIndex = 0;
				}
				else if (selectedItemIndex == 6) {
					printf("pushed Exited");
					onDeactivate();
					return Signal::GoToMainMenu;
				}
			}
		}
	}
	return Signal::None;
}
