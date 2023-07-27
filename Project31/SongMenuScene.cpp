#include "SongMenuScene.h"
#include <SFML/Audio.hpp>
#include <algorithm>
// tmep max num
#define MAX_NUM 6

std::string difficulties[3] = { "Normal", "Hard", "Expert" };

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
                    // 앨범 이미지 경로 찾기
                    if (subEntry.path().filename() == "image.jpg" || subEntry.path().filename() == "image.png") {
                        songInfo.imagePath = subEntry.path().string();
                    }
                    // 노래 파일 경로
                    else if (subEntry.path().extension() == ".mp3" || subEntry.path().extension() == ".ogg") {
                        songInfo.songPath = subEntry.path().string();
                        am.LoadMusic(songInfo.songNameStr,songInfo.songPath);
                    }
                    // 채보 파일 경로
                    else if (subEntry.path().extension() == ".osu") {
                        // 난이도 존재 유무.
                        for (int i = 0; i < 3; i++) {
                            if (subEntry.path().filename().string() == difficulties[i] + ".osu") {
                                songInfo.difficultiesExist.push_back(i);
                                break;
                            }
                        }
                    }
                }

                songInfos.push_back(songInfo);
                i++;
            }
        }
    }

    albumImage = std::make_unique<AlbumArt>(sf::Vector2f(200, 200), sf::Vector2f(100, 100), songInfos[selectedItemIndex].imagePath);
}


SongMenuScene::~SongMenuScene() {

}

void SongMenuScene::draw(sf::RenderWindow& window) {
    //곡 목록 표시
    for (int i = 0; i < songInfos.size(); i++)
    {
        sf::Text songName;
        songName.setFont(font);
        songName.setString(songInfos[i].songNameStr);
        songName.setPosition(sf::Vector2f(width / 2, height / (MAX_NUM + 1) * (i + 1)));

        if (i == selectedItemIndex) {// 선택된 곡은 붉은 색으로
            songName.setFillColor(sf::Color::Red);
        }
        else {
            songName.setFillColor(sf::Color::White);
        }

        window.draw(songName);
    }

    // 난이도 목록
    float spacing = 50.f;  // 각 난이도 텍스트 사이의 공간
    float currentPositionX = 100.f;  // 첫 번째 난이도 텍스트 시작점

    std::vector<int> difficultiesCopy = songInfos[selectedItemIndex].difficultiesExist;
    std::reverse(difficultiesCopy.begin(), difficultiesCopy.end());

    for (const auto& difficulty : difficultiesCopy) {
        sf::Text difficultyText;
        difficultyText.setFont(font);
        difficultyText.setString(difficulties[difficulty]);

        switch (difficulty)
        {
        case 0:
            currentPositionX = 100.f;
            break;
        case 1:
            currentPositionX = 177.f;
            break;
        case 2:
            currentPositionX = 232.f;
            break;
        }
        difficultyText.setPosition(sf::Vector2f(currentPositionX, 300));
        difficultyText.setCharacterSize(20);

        if (difficulty == selectedDifficultyIndex) {
            difficultyText.setFillColor(sf::Color::Red);
        }
        else {
            difficultyText.setFillColor(sf::Color::White);
        }

        window.draw(difficultyText);

        // 다음 난이도 텍스트의 위치를 계산
        currentPositionX += difficultyText.getLocalBounds().width + spacing;
    }

    // 앨범 이미지 그리기
    albumImage->draw(window);
}

void SongMenuScene::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        selectedItemIndex--;  // 먼저 인덱스를 감소

        am.PlaySound("menu_select");
        selectedDifficultyIndex = 0;

        // Stop the current music and play the selected one
        am.StopMusic(songInfos[selectedItemIndex + 1].songNameStr);
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);

        albumImage->setTexturePath(songInfos[selectedItemIndex].imagePath);
    }
}

void SongMenuScene::MoveDown() {
    if (selectedItemIndex + 1 < songInfos.size()) {
        selectedItemIndex++;  // 먼저 인덱스를 증가

        am.PlaySound("menu_select");
        selectedDifficultyIndex = 0;

        // Stop the current music and play the selected one
        am.StopMusic(songInfos[selectedItemIndex - 1].songNameStr);
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);

        albumImage->setTexturePath(songInfos[selectedItemIndex].imagePath);
    }
}

void SongMenuScene::MoveLeft() {
    if (selectedDifficultyIndex > 0) {
        selectedDifficultyIndex--;
    }
}

void SongMenuScene::MoveRight() {
    if (selectedDifficultyIndex < songInfos[selectedItemIndex].difficultiesExist.size()-1) {
        selectedDifficultyIndex++;
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
        else if (event.key.code == sf::Keyboard::Right) {
            MoveRight();
        }
        else if (event.key.code == sf::Keyboard::Left) {
            MoveLeft();
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

void SongMenuScene::onActivate() {
    if (songInfos.size() > 0) {
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);
    }
}

void SongMenuScene::onDeactivate() {
    if (songInfos.size() > 0) {
        am.StopMusic(songInfos[selectedItemIndex].songNameStr);
    }
}
