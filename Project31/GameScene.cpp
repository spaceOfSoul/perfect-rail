#include "GameScene.h"
#define _BV(n) (1<<n)

GameScene::GameScene(float width, float height)
: am(AudioManager::Instance())
, gm(GameManager(am, noteInScreen))
, sm(SettingsManager::Instance())
, note_plate(platePosition, 0)
, comboText(sf::Color(128, 128, 128, 255), width / 2, comboHeight)
, judgeText(sf::Color(128, 128, 128, 255), width / 2, judgeHeight)
, resultRectangle(width, height, font)
, screen_width(width), screen_height(height)
, input_ui(130, 300, 50, (int)width, (int)height)
, deadPannel(0,0)
{
    for (int i = 0; i < 4; i++) 
        keyPushed[i] = false;
    
    if (!font.loadFromFile("fonts\\arial.ttf")) {
        printf("폰트가 없음!");
    }

    comboText.setFont(font);
    judgeText.setFont(font);
    am.LoadMusic("Result", "./bgm/Result.wav");

    finish_process = false;
    input_process = 0;
    isAlive = true;

    judgeY = 440;

    hp_bar = new HpBar(screen_width / 2 + plateWidth / 2, 75, 25, 375, font, 15);
}

GameScene::~GameScene() {
    free(hp_bar);
}

void GameScene::onActivate() {
	SceneManager& scene_manager = SceneManager::getInstance();
	printf("on Activate\n");
    musicStarted = false;
    isAlive = true;
    hp = 100;
    input_process = 0;

    judgeY = 440 - sm.GetJudgeLine_Y();
    
    for (int i = 0; i < 4; i++)
        processedIndex[i] = 0;

    note_speed = sm.GetNoteSpeed();
    input_ui.initInput();
    initialize();
	setSongInfo(scene_manager.currentPlaySong, scene_manager.currentDifficultyIndex);
    gm.init(song_data);
    noteClock.restart();
}

void GameScene::initialize() {
    game_finished = false;
    finish_process = false;
    input_process = 0;
    isAlive = true;

    hp = 100;

    //Game Setting
    noteTravelTime = ((judgeY - note_startPos_Y) / note_speed) + ((double)sm.GetTimeSync()/(double)1000);

    // UI Setting
    // Buttons
    const int start_pos = 255;
    const int buttonY = 500;
    const int bt_distance = 80;

    for (int i = 0; i < 4; i++) {
        buttons[i].setSize(sf::Vector2f(50, 50));
        buttons[i].setFillColor(sf::Color(128, 128, 128));
        buttons[i].setPosition(start_pos + bt_distance * i, buttonY);
    }

    judgeLine.setSize(sf::Vector2f(350, 20));
    judgeLine.setPosition(225, judgeY);
    judgeLine.setFillColor(sf::Color(128, 128, 128));

    // 콤보
    comboText.setPosition(400, comboHeight);
    comboText.setCombo(0);

    // 판정
    judgeText.setPosition(400, judgeHeight);
    judgeText.setJudgement(10);

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

    judgeY = sm.GetJudgeLine_Y();
}

void GameScene::update(float dt) {
    // note clock
    if (!noteClockStarted) {
        noteClock.restart();
        noteClockStarted = true;
    }

    // music clock
    // Music click is slower then Note clock.
    if (!musicStarted && noteClock.getElapsedTime().asSeconds() >= noteTravelTime) {
        am.PlayMusic(songInfo.songNameStr);
        musicStarted = true;
    }

    if (musicStarted && am.GetMusicStatus() == sf::Music::Stopped && isAlive) {
        game_finished = true;
        input_process |= _BV(0); // sound
        if (finish_process) {
            resultRectangle.setResult(gm.getAccuracy(), gm.getScore(), gm.getMaxCombo(), gm.getTargetPass(), false);
            am.StopMusic(songInfo.songNameStr);
            am.PlayMusic("Result");

            ResultData data(gm.getAccuracy(), gm.getScore(), gm.getMaxCombo(), gm.getTargetPass(), username); // 현재 결과

            Results existingResults = SaveResult::loadFromDirectory(get_appdata_roaming_path().append("\\perfectRail\\").append(songInfo.songNameStr));
            existingResults.add(data);

            std::sort(existingResults.results.begin(), existingResults.results.end(), [](const ResultData& a, const ResultData& b) {
                return a.score > b.score;
             });

            if (existingResults.size() > 10) {
                existingResults.results.resize(10);
            }
            // 최종 하이스코어 저장
            SaveResult::saveToDirectory(existingResults, get_appdata_roaming_path().append("\\perfectRail\\").append(songInfo.songNameStr));
        }
    }

    // sound play
    // 0 1 : game finished
    // 1 1 : sound played
    if ((_BV(0) & input_process) && !(_BV(1) & input_process)) {
        am.PlayEventSound("applause");
        input_process |= _BV(1);
    }

    // note drawing
    if (isAlive) {
        long long noteTime = noteClock.getElapsedTime().asMilliseconds();

        for (int lane = 0; lane < 4; lane++) {
            for (int i = processedIndex[lane]; i < song_data.NotePoints[lane].size(); ++i) {
                long long time = song_data.NotePoints[lane][i].first;

                if (noteTime < time) {
                    break; // 시간이 아직 안됐으면 종료
                }

                int xPosition = note_startPos_X + note_distance * lane;
                sf::Color color = sf::Color::Green;

                // Generate Note
                Note note(lane, xPosition, note_startPos_Y, note_size, color, time, false);
                noteInScreen.push_back(note);
                processedIndex[lane] = i + 1;
            }
        }
    }

    gm.checkMiss(judgeText, comboText);

    comboText.animation(dt);
    judgeText.animation(dt);
    hp = gm.getHP();
    hp_bar->setHP(hp);

    if (hp <= 0) {
        am.StopMusic(songInfo.songNameStr);
        if (isAlive) {
            printf("player dead\n");
            am.PlayEventSound("GameOver");
        }
        isAlive = false;
    }

    // note drawing logic
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
    window.draw(judgeLine);

    for (const Note& note : noteInScreen)
        window.draw(note);

    window.draw(note_plate);

    for (int i = 0; i < 4; i++)
        window.draw(buttons[i]);

    window.draw(comboText);
    window.draw(judgeText);
    scoreText.setString(std::to_string(gm.getScore()));

    std::string accurateStr = std::to_string(gm.getAccuracy());
    accurateStr = accurateStr.substr(0, accurateStr.find(".") + 3) + "%";
    accurateText.setString(accurateStr);

    // 콤보, 스코어, hp 그리기
    window.draw(scoreText);
    window.draw(accurateText);
    window.draw(*hp_bar);

    if (!isAlive) {
        window.draw(deadPannel);
        return;
    }

    if (game_finished) {
        if (!finish_process) { // 이름 입력
            window.draw(input_ui);
        }
        else { // 결과창 표시
            window.draw(resultRectangle);
        }
    }
}

Signal GameScene::handleInput(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            if (game_finished && !finish_process) // when running input process
                return Signal::None;
            onDeactivate();
            return Signal::GoToSongMenu;
        }
        else if (event.key.code == sf::Keyboard::D) {
            if (!keyPushed[0]) {
                gm.keyDownProcess(0, judgeText, comboText);
                buttons[0].setFillColor(sf::Color(65, 105, 225));
                keyPushed[0] = true;
            }
        }
        else if (event.key.code == sf::Keyboard::F) {
            if (!keyPushed[1]) {
                gm.keyDownProcess(1, judgeText, comboText);
                buttons[1].setFillColor(sf::Color(65, 105, 225));
                keyPushed[1] = true;
            }
        }
        else if (event.key.code == sf::Keyboard::J) {
            if (!keyPushed[2]) {
                gm.keyDownProcess(2, judgeText, comboText);
                buttons[2].setFillColor(sf::Color(65, 105, 225));
                keyPushed[2] = true;
            }
        }
        else if (event.key.code == sf::Keyboard::K) {
            if (!keyPushed[3]) {
                gm.keyDownProcess(3, judgeText, comboText);
                buttons[3].setFillColor(sf::Color(65, 105, 225));
                keyPushed[3] = true;
            }
        }
        else if (event.key.code == sf::Keyboard::Enter) { // enter
            if (!finish_process) { // get username
                // get user name
                username = input_ui.getUserName();
                if (username.size()>0)
                    finish_process = true;
            }
            else if (!isAlive || game_finished) { // go to song menu
                onDeactivate();
                return Signal::GoToSongMenu;
            }
        }

        if (game_finished) { // 방향키는 여기서만 활성화
            if (event.key.code == sf::Keyboard::Left) { // 이름 좌우 이동
                input_ui.setIndex(false);
            }
            else if (event.key.code == sf::Keyboard::Right) {
                input_ui.setIndex(true);
            }else if (event.key.code == sf::Keyboard::Up) { // 알파벳 변경
                input_ui.setChar(true);
            }
            else if (event.key.code == sf::Keyboard::Down) {
                input_ui.setChar(false);
            }
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::D) {
            keyPushed[0] = false;
            buttons[0].setFillColor(sf::Color(128, 128, 128));
        }
        else if (event.key.code == sf::Keyboard::F) {
            keyPushed[1] = false;
            buttons[1].setFillColor(sf::Color(128, 128, 128));
        }
        else if (event.key.code == sf::Keyboard::J) {
            keyPushed[2] = false;
            buttons[2].setFillColor(sf::Color(128, 128, 128));
        }
        else if (event.key.code == sf::Keyboard::K) {
            keyPushed[3] = false;
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

    song_data = {};

	//file path
	std::string filePath = generateFilePath(songInfo, difficultyIndex);

    int file_opened = LoadMapFile(filePath, song_data);

    if (!file_opened)
        printf("%s open failed!\n",filePath.c_str());
    else
        printf("Load %s\n", filePath.c_str());
}