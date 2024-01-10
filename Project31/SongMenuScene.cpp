#include "SongMenuScene.h"
#include <SFML/Audio.hpp>
#include <algorithm>

std::string difficulties[3] = { "Normal", "Hard", "Expert" };

SongMenuScene::SongMenuScene(float width, float height) 
    :am(AudioManager::Instance()), songList(VerticalList(width, height)) {
    this->width = width;
    this->height = height;
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
                SongInfo songInfo;

                songInfo.songNameStr = entry.path().filename().string();

                for (const auto& subEntry : std::filesystem::directory_iterator(entry.path())) {
                    // �ٹ� �̹��� ��� ã��
                    if (subEntry.path().filename() == "image.jpg" || subEntry.path().filename() == "image.png") {
                        songInfo.imagePath = subEntry.path().string();
                    }
                    // �뷡 ���� ���
                    else if (subEntry.path().extension() == ".mp3" || subEntry.path().extension() == ".ogg") {
                        songInfo.songPath = subEntry.path().string();
                        am.LoadMusic(songInfo.songNameStr,songInfo.songPath);
                        printf("%s\n", songInfo.songPath.c_str());
                    }
                    // ä�� ���� ���
                    else if (subEntry.path().extension() == ".osu") {
                        // ���̵� ���� ����.
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
    albumImage = std::make_unique<AlbumArt>(sf::Vector2f(250, 250), sf::Vector2f(50, 30), songInfos[selectedItemIndex].imagePath); // size, pos

    difficultyRegionRect.setFillColor(sf::Color(40, 40, 40, 200));
    difficultyRegionRect.setSize(sf::Vector2f(250,50));
    difficultyRegionRect.setPosition(sf::Vector2f(50,230));

    region_highscore = std::make_unique<HighscorePannel>(30,290, font);
    songList.setPos(-60,-30);
}


SongMenuScene::~SongMenuScene() {

}

void SongMenuScene::draw(sf::RenderWindow& window) {
    //�� ��� ǥ��
    songList.draw(window);

    float PositionX = 63.f;  // ù ��° ���̵� �ؽ�Ʈ ������

    // �ٹ� �̹��� �׸���
    albumImage->draw(window);
    window.draw(difficultyRegionRect);
    // ���̵� ���
    for (const auto& difficulty : songInfos[selectedItemIndex].difficultiesExist) {
        sf::Text difficultyText;
        difficultyText.setFont(font);
        difficultyText.setString(difficulties[difficulty]);

        switch (difficulty)
        {
        case 0:
            difficultyText.setPosition(sf::Vector2f(PositionX, 240));
            break;
        case 1:
            difficultyText.setPosition(sf::Vector2f((PositionX + 280) / 2 - difficultyText.getLocalBounds().width / 2+10, 240));
            break;
        case 2:
            difficultyText.setPosition(sf::Vector2f(280 - difficultyText.getLocalBounds().width+20, 240));
            break;
        }
        difficultyText.setCharacterSize(25);

        if (difficulty == songInfos[selectedItemIndex].difficultiesExist[selectedDifficultyIndex]) {
            difficultyText.setFillColor(sf::Color::Red);
        }
        else {
            difficultyText.setFillColor(sf::Color::White);
        }

        window.draw(difficultyText);
    }

    window.draw(*region_highscore);
}

void SongMenuScene::MoveUp() {
    selectedDifficultyIndex = 0;
    songList.MoveUp();
    updateSelectedItem();
    am.PlayEventSound("menu_select");
}

void SongMenuScene::MoveDown() {
    selectedDifficultyIndex = 0;
    songList.MoveDown();
    updateSelectedItem();
    am.PlayEventSound("menu_select");
}

void SongMenuScene::updateSelectedItem() {
    selectedItemIndex = songList.getCurrentIndex();

    // ���� ���õ� ���� ������ ������Ʈ�մϴ�.
    const SongInfo& currentSong = songInfos[selectedItemIndex];
    am.StopMusic(currentSong.songNameStr); // ������ ��� ���̴� ������ �����մϴ�.
    am.PlayMusic(currentSong.songNameStr); // ���ο� ���� ����մϴ�.

    // �ٹ� �̹����� ����� �г� ������Ʈ
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
	// ������
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
