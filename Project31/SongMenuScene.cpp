#include "SongMenuScene.h"
#include <SFML/Audio.hpp>
#include <algorithm>

std::string difficulties[3] = { "Normal", "Hard", "Expert" };

SongMenuScene::SongMenuScene(float width, float height) 
    :am(AudioManager::Instance()), songList(VerticalList(width, height)) {
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
                        printf("%s\n", songInfo.songPath.c_str());
                    }
                    // 채보 파일 경로
                    else if (subEntry.path().extension() == ".osu") {
                        // 난이도 존재 유무.
                        for (int i = 0; i < 3; i++) {
                            if (subEntry.path().filename().string().find(difficulties[i]) != std::string::npos) {
                                songInfo.difficultiesExist.push_back(i);
                                break;
                            }
                        }
                        std::sort(songInfo.difficultiesExist.begin(), songInfo.difficultiesExist.end());
                    }
                }
                songInfos.push_back(songInfo);
                songList.addItem(songInfo.songNameStr);
                i++;
            }
        }
    }
    selectedItemIndex = songList.getCurrentIndex();
    albumImage = std::make_unique<AlbumArt>(sf::Vector2f(200, 200), sf::Vector2f(50, 50), songInfos[selectedItemIndex].imagePath);
    region_highscore = std::make_unique<HighscorePannel>(50,290, font);
}


SongMenuScene::~SongMenuScene() {

}

void SongMenuScene::draw(sf::RenderWindow& window) {
    //곡 목록 표시
    songList.draw(window);

    float spacing = 50.f;  // 각 난이도 텍스트 사이의 공간
    float currentPositionX = 100.f;  // 첫 번째 난이도 텍스트 시작점
    // 난이도 목록
    for (const auto& difficulty : songInfos[selectedItemIndex].difficultiesExist) {
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
        difficultyText.setPosition(sf::Vector2f(currentPositionX, 260));
        difficultyText.setCharacterSize(20);

        if (difficulty == songInfos[selectedItemIndex].difficultiesExist[selectedDifficultyIndex]) {
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
    window.draw(*region_highscore);
}

void SongMenuScene::MoveUp() {
    songList.MoveUp();
    updateSelectedItem();
    am.PlayEventSound("menu_select");
}

void SongMenuScene::MoveDown() {
    songList.MoveDown();
    updateSelectedItem();
    am.PlayEventSound("menu_select");
}

void SongMenuScene::updateSelectedItem() {
    selectedItemIndex = songList.getCurrentIndex();

    // 현재 선택된 곡의 정보를 업데이트합니다.
    const SongInfo& currentSong = songInfos[selectedItemIndex];
    am.StopMusic(currentSong.songNameStr); // 이전에 재생 중이던 음악을 정지합니다.
    am.PlayMusic(currentSong.songNameStr); // 새로운 곡을 재생합니다.

    // 앨범 이미지와 고득점 패널 업데이트
    albumImage->setTexturePath(currentSong.imagePath);
    Results results = SaveResult::loadFromDirectory(get_appdata_roaming_path().append("\\perfectRail\\").append(currentSong.songNameStr));
    region_highscore->setScores(results);
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
        else if (event.key.code == sf::Keyboard::Right) {
            MoveRight();
        }
        else if (event.key.code == sf::Keyboard::Left) {
            MoveLeft();
        }
        else if (event.key.code == sf::Keyboard::Return)
        {
            SceneManager& sceneManager = SceneManager::getInstance();
            sceneManager.setGameScene(songInfos[selectedItemIndex], selectedDifficultyIndex);
            return Signal::GoToPlayScene;
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
    selectedItemIndex = songList.getCurrentIndex();
    if (songInfos.size() > 0) {
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);
    }
    Results results = SaveResult::loadFromDirectory(get_appdata_roaming_path().append("\\perfectRail\\").append(songInfos[selectedItemIndex].songNameStr));
    region_highscore->setScores(results);
}

void SongMenuScene::onDeactivate() {
    if (songInfos.size() > 0) {
        am.StopMusic(songInfos[selectedItemIndex].songNameStr);
    }
}
