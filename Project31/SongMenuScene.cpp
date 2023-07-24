#include "SongMenuScene.h"
#include <SFML/Audio.hpp>
// tmep max num
#define MAX_NUM 6

SongMenuScene::SongMenuScene(float width, float height):am(AudioManager::Instance()) {
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("폰트가 없음.\n");
	}

	std::filesystem::path directoryPath("Songs");

    if (std::filesystem::exists(directoryPath) && std::filesystem::is_directory(directoryPath))
    {
        int i = 0;
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        {
            if (std::filesystem::is_directory(entry))
            {
                sf::Text text;
                text.setFont(font);
                text.setString(entry.path().filename().string());
                text.setPosition(sf::Vector2f(width / 2, height / (MAX_NUM + 1) * (i + 1)));

                for (const auto& subEntry : std::filesystem::directory_iterator(entry.path())) {
                    if (subEntry.path().filename() == "image.jpg" || subEntry.path().filename() == "image.png") {
                        songImagePaths.push_back(subEntry.path().string());
                        break;
                    }
                }

                if (i == selectedItemIndex) {
                    text.setFillColor(sf::Color::Red);
                }else
                    text.setFillColor(sf::Color::White);

				song_list.push_back(text);
                i++;
            }
        }
    }
    albumImage = std::make_unique<AlbumArt>(sf::Vector2f(200, 200), sf::Vector2f(100, 100), songImagePaths[selectedItemIndex]);
}

SongMenuScene::~SongMenuScene() {

}

void SongMenuScene::draw(sf::RenderWindow& window) {
	for (int i = 0; i < song_list.size(); i++)
	{
		window.draw(song_list[i]);
	}
    albumImage->draw(window);
}

void SongMenuScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0 && selectedItemIndex < song_list.size())
	{
        am.PlaySound("menu_select");
		song_list[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
        albumImage->setTexturePath(songImagePaths[selectedItemIndex]);

		song_list[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void SongMenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < song_list.size())
	{
        am.PlaySound("menu_select");
		song_list[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
        albumImage->setTexturePath(songImagePaths[selectedItemIndex]);
		song_list[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

Signal SongMenuScene::handleInput(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyReleased)
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
            printf("pressed %d\n", pressedItem);
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            return Signal::GoToMainMenu;
        }
    }
    return Signal::None;
}

void SongMenuScene::update(float dt) {
	// 구현부
}
