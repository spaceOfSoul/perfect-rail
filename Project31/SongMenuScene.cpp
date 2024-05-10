#include "SongMenuScene.h"
#include <SFML/Audio.hpp>
#include <algorithm>

std::string difficulties[3] = { "Normal", "Hard", "Expert" };

SongMenuScene::SongMenuScene(float width, float height, sf::Font& font)
    :am(AudioManager::Instance()), songList(VerticalList(width, height)), font(font), sm(SettingsManager::Instance()) {
    this->width = width;
    this->height = height;

}


SongMenuScene::~SongMenuScene() {

}

void SongMenuScene::draw(sf::RenderWindow& window) {

    //// 곡 목록 배경
    //window.draw(backPlate);

    //// 목록 배경
    //window.draw(listPlate);

    //곡 목록 표시
    songList.draw(window);

    float PositionX = 63.f;  // 첫 번째 난이도 텍스트 시작점

    // 앨범 이미지 그리기
    albumImage->draw(window);
    window.draw(difficultyRegionRect);
    // 난이도 목록
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

    // 곡 목록 살짝 위를 가림..
    //window.draw(seletedPlate);

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

    // 현재 선택된 곡의 정보를 업데이트.
    const SongInfo& currentSong = songInfos[selectedItemIndex];
    am.StopMusic(currentSong.songNameStr);
    am.PlayMusic(currentSong.songNameStr);

    // 앨범 이미지와 고득점 패널 업데이트
    albumImage->setTexturePath(currentSong.imagePath);
    
#ifdef WIN32
    Results results = SaveResult::loadFromDirectory(get_appdata_roaming_path().append("\\perfectRail\\").append(currentSong.songNameStr));
#else
    Results results = SaveResult::loadFromDirectory(get_appdata_roaming_path().append("/perfectRail/").append(currentSong.songNameStr));
#endif

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
	// segment music play
    try {
        sf::Music& music = am.getMusic();
        sf::Int32 current_music_time = music.getPlayingOffset().asMilliseconds();
        if (current_music_time >= 20000)
            am.SetMusicTime(sf::seconds(0));
        else if (current_music_time >= 15000) {
            float time_left = 20000 - current_music_time;
            float volume_factor = time_left / 5000.0f;
            currentVolume = sm.GetMusicVolume() * volume_factor;
            am.SetMusicVolume(currentVolume);
        }
        else{
            currentVolume = sm.GetMusicVolume();
            am.SetMusicVolume(currentVolume);
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void SongMenuScene::onActivate() {
    // song list
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
                    else if (subEntry.path().extension() == ".ogg" || subEntry.path().extension() == ".mp3") { // mp3 파일은 공식적으로는 지원되지 않는다고 함.
                        songInfo.songPath = subEntry.path().string();
                        am.LoadMusic(songInfo.songNameStr, songInfo.songPath);
                        std::cerr << songInfo.songPath << std::endl;
                    }
                    // 채보 파일 경로
                    else if (subEntry.path().extension() == ".ptr") {
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
    songList.setPos(-60, -30);

    // album image
    selectedItemIndex = songList.getCurrentIndex();
    albumImage = std::make_unique<AlbumArt>(sf::Vector2f(250, 250), sf::Vector2f(50, 30), songInfos[selectedItemIndex].imagePath); // size, pos

    // difficulty
    difficultyRegionRect.setFillColor(sf::Color(40, 40, 40, 200));
    difficultyRegionRect.setSize(sf::Vector2f(250, 50));
    difficultyRegionRect.setPosition(sf::Vector2f(50, 230));

    // before score region
    region_highscore = std::make_unique<HighscorePannel>(30, 290, font);

    #ifdef WIN32
    Results results = SaveResult::loadFromDirectory(get_appdata_roaming_path().append("\\perfectRail\\").append(songInfos[selectedItemIndex].songNameStr));
    #else
    Results results = SaveResult::loadFromDirectory(get_appdata_roaming_path().append("/perfectRail/").append(songInfos[selectedItemIndex].songNameStr));
    #endif
    region_highscore->setScores(results);

    currentVolume = sm.GetMusicVolume();
    // play music
    if (songInfos.size() > 0) {
        am.PlayMusic(songInfos[selectedItemIndex].songNameStr);
    }

    //// back plate
    //backPlate.setPosition(0,0);
    //backPlate.setFillColor(sf::Color(204,204,204));
    //backPlate.setSize(sf::Vector2f(width, height));

    //// selected plate
    //seletedPlate.setPosition(330, 0);
    //seletedPlate.setFillColor(sf::Color(204, 204, 204));
    //seletedPlate.setSize(sf::Vector2f(470, 40));

    //// list plate
    //listPlate.setPosition(330, 30);
    //listPlate.setFillColor(sf::Color(0, 0, 0));
    //listPlate.setSize(sf::Vector2f(500, 550));
}

void SongMenuScene::onDeactivate() {
    if (songInfos.size() > 0) {
        am.StopMusic(songInfos[selectedItemIndex].songNameStr);
    }
}
