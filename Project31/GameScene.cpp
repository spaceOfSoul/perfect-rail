#include "GameScene.h"


GameScene::GameScene(float width, float height) : am(AudioManager::Instance()) {
    for (int i = 0; i < 4; i++) {
        keyPushed[i] = false;
    }
    if (!font.loadFromFile("fonts\\arial.ttf")) {
        printf("폰트가 없음!");
    }
}

GameScene::~GameScene() {

}

void GameScene::onActivate() {
	SceneManager& scene_manager = SceneManager::getInstance();
	printf("on Activate\n");
    musicStarted = false;
    processedIndex = 0;
    initialize();
	setSongInfo(scene_manager.currentPlaySong, scene_manager.currentDifficultyIndex);
    musicStartClock.restart();
}

void GameScene::initialize() {
    // Plate rectangle
    plate.setSize(sf::Vector2f(plateWidth, 600));
    plate.setFillColor(sf::Color::White);
    plate.setPosition(platePosition, 0);

    // Note place
    notePlace.setSize(sf::Vector2f(350, 475));
    notePlace.setFillColor(sf::Color::Black);
    notePlace.setPosition(225, 0);

    // Buttons
    const int start_pos = 255;
    const int buttonY = 500;
    const int bt_distance = 80;

    for (int i = 0; i < 4; i++) {
        buttons[i].setSize(sf::Vector2f(50, 50));
        buttons[i].setFillColor(sf::Color(128, 128, 128));
        buttons[i].setPosition(start_pos + bt_distance * i, buttonY);
    }

    // 콤보
    float comboX = platePosition + plateWidth / 2 - comboFontSize /2;
    comboText.setFont(font);
    comboText.setCharacterSize(comboFontSize);
    comboText.setFillColor(sf::Color(128, 128, 128, 255)); // 회색으로 설정
    comboText.setPosition(comboX, comboHeight);

    // 스코어
    // Out Pannel
    //scorePannel_outer.setSize(scorePannel_outerSize);
    //scorePannel_outer.setFillColor(sf::Color::White);
    //scorePannel_outer.setPosition(scorePos);

    //// Inner Pannel
    //scorePannel_outer.setSize(scorePannel_innerSize);
    //scorePannel_outer.setFillColor(sf::Color::Black);
    //scorePannel_outer.setPosition(scorePos);

    // Score Text
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(scorePos);

    // 정확도
    accurateText.setFont(font);
    accurateText.setCharacterSize(24);
    accurateText.setFillColor(sf::Color(128, 128, 128));
    accurateText.setPosition(accPos);
}

void GameScene::update(float dt) {
    if (!musicStarted && musicStartClock.getElapsedTime().asSeconds() >= 3.0f) {
        am.PlayMusic(songInfo.songNameStr);
        musicStarted = true;
    }
     float musicTime = am.getMusic().getPlayingOffset().asMilliseconds();


     for (int i = processedIndex; i < song_data.NotePoints.size(); ++i) {
         int time = song_data.NotePoints[i].first;
         const std::array<int, 4>& lanes = song_data.NotePoints[i].second;

         if (musicTime < time) {
             break; // 시간이 아직 안됐으면 종료
         }

         for (int j = 0; j < 4; j++) {
             if (lanes[j] > 0) {
                 bool isLong = (lanes[j] == 2);
                 int xPosition = note_startPos + note_distance * j;
                 sf::Color color = sf::Color::Green;
                 float size = 70;
                 Note note(j, xPosition, -10, size, color, isLong);
                 noteInScreen.push_back(note);
             }
         }
         processedIndex = i + 1;
     }

     for (std::list<Note>::iterator iter = noteInScreen.begin(); iter != noteInScreen.end(); ) {
         sf::Vector2f pos = iter->getPosition();
         pos.y += note_speed * dt;
         iter->setPosition(pos);
         if (iter->position.y > 600) {
             iter = noteInScreen.erase(iter);
         }
         else {
             ++iter;
         }
     }
}

void GameScene::onDeactivate() {
    noteInScreen.clear();
}


void GameScene::draw(sf::RenderWindow& window) {
    window.draw(plate);
    window.draw(notePlace);

    for (const Note& note : noteInScreen) {
        window.draw(note);
    }

    for (int i = 0; i < 4; i++) {
        window.draw(buttons[i]);
    }

    int Combo = 24; // TEST
    int Score = 1000; // TEST
    double Accurate = 98.f; // TEST

    comboText.setString(std::to_string(Combo));
    scoreText.setString(std::to_string(Score));

    std::string accurateStr = std::to_string(Accurate);
    accurateStr = accurateStr.substr(0, accurateStr.find(".") + 3) + "%";
    accurateText.setString(accurateStr);

    // 콤보, 스코어, 정확도 텍스트 그리기
    window.draw(comboText);
    window.draw(scoreText);
    window.draw(accurateText);
}

Signal GameScene::handleInput(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            onDeactivate();
            return Signal::GoToSongMenu;
        }
        else if (event.key.code == sf::Keyboard::D) {
            buttons[0].setFillColor(sf::Color(65, 105, 225));
        }
        else if (event.key.code == sf::Keyboard::F) {
            buttons[1].setFillColor(sf::Color(65, 105, 225));
        }
        else if (event.key.code == sf::Keyboard::J) {
            buttons[2].setFillColor(sf::Color(65, 105, 225));
        }
        else if (event.key.code == sf::Keyboard::K) {
            buttons[3].setFillColor(sf::Color(65, 105, 225));
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::D) {
            buttons[0].setFillColor(sf::Color(128, 128, 128));
        }
        else if (event.key.code == sf::Keyboard::F) {
            buttons[1].setFillColor(sf::Color(128, 128, 128));
        }
        else if (event.key.code == sf::Keyboard::J) {
            buttons[2].setFillColor(sf::Color(128, 128, 128));
        }
        else if (event.key.code == sf::Keyboard::K) {
            buttons[3].setFillColor(sf::Color(128, 128, 128));
        }
    }

	return Signal::None;
}

void reset() {

}

std::string GameScene::generateFilePath(const SongInfo& songInfo, int difficultyIndex) {
	std::string difficulties[3] = { "Normal", "Hard", "Expert" };
	std::string filePath = "Songs/" + songInfo.songNameStr + "/" + difficulties[songInfo.difficultiesExist[difficultyIndex]] + ".osu";
	return filePath;
}

void GameScene::setSongInfo(const SongInfo &songInfo, int difficulty) {
	this->songInfo = songInfo;
	this->difficultyIndex = difficulty;

	//file path
	std::string filePath = generateFilePath(songInfo, difficultyIndex);

    int file_opened = LoadMapFile(filePath, song_data);

    if (!file_opened)
        printf("%s open failed!\n",filePath.c_str());
    else
        printf("Load %s\n", filePath.c_str());
}