#include "SongMenuScene.h"

// tmep max num
#define MAX_NUM 6

SongMenuScene::SongMenuScene(float width, float height) {
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		printf("��Ʈ�� ����.\n");
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
                text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

				song_list.push_back(text);
                i++;
            }
        }
    }
}

SongMenuScene::~SongMenuScene() {

}

void SongMenuScene::draw(sf::RenderWindow& window) {
	for (int i = 0; i < song_list.size(); i++)
	{
		window.draw(song_list[i]);
	}
}

void SongMenuScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0 && selectedItemIndex < song_list.size())
	{
		song_list[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		song_list[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void SongMenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < song_list.size())
	{
		song_list[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
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
            if (pressedItem) {
                return Signal::GoToSongMenu;
            }
            printf("pressed %d\n", pressedItem);
        }
    }
    return Signal::None;
}

void SongMenuScene::update(float dt) {
	// ������
}