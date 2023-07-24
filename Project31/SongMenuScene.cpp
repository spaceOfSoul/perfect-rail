#include "SongMenuScene.h"
#include <SFML/Audio.hpp>
// tmep max num
#define MAX_NUM 6

SongMenuScene::SongMenuScene(float width, float height) :am(AudioManager::Instance()) {
    this->width = width;
    this->height = height;
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
                SongInfo songInfo;

                songInfo.songNameStr = entry.path().filename().string();

                for (const auto& subEntry : std::filesystem::directory_iterator(entry.path())) {
                    if (subEntry.path().filename() == "image.jpg" || subEntry.path().filename() == "image.png") {// 앨범이미지
                        songInfo.imagePath = subEntry.path().string();
                    }
                    else if (subEntry.path().extension() == ".mp3" || subEntry.path().extension() == ".ogg") {//오디오파일 찾기
                        songInfo.songPath = subEntry.path().string();
                        am.LoadMusic(songInfo.songNameStr,songInfo.songPath);
                    }
                }

                songInfos.push_back(songInfo);
                i++;
            }
        }
    }

    if (songInfos.size() > 0) {
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);
    }

    albumImage = std::make_unique<AlbumArt>(sf::Vector2f(200, 200), sf::Vector2f(100, 100), songInfos[selectedItemIndex].imagePath);
}


SongMenuScene::~SongMenuScene() {

}

void SongMenuScene::draw(sf::RenderWindow& window) {
    for (int i = 0; i < songInfos.size(); i++)
    {
        sf::Text songName;
        songName.setFont(font);
        songName.setString(songInfos[i].songNameStr);
        songName.setPosition(sf::Vector2f(width / 2, height / (MAX_NUM + 1) * (i + 1)));

        if (i == selectedItemIndex) {
            songName.setFillColor(sf::Color::Red);
        }
        else {
            songName.setFillColor(sf::Color::White);
        }

        window.draw(songName);
    }

    albumImage->draw(window);
}

void SongMenuScene::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        am.PlaySound("menu_select");
        selectedItemIndex--;

        // Stop the current music and play the selected one
        am.StopMusic(songInfos[selectedItemIndex + 1].songNameStr);
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);

        albumImage->setTexturePath(songInfos[selectedItemIndex].imagePath);
    }
}

void SongMenuScene::MoveDown()
{
    if (selectedItemIndex + 1 < songInfos.size())
    {
        am.PlaySound("menu_select");
        selectedItemIndex++;

        // Stop the current music and play the selected one
        am.StopMusic(songInfos[selectedItemIndex - 1].songNameStr);
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);

        albumImage->setTexturePath(songInfos[selectedItemIndex].imagePath);
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
