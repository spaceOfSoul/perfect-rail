#include "GameScene.h"

GameScene::GameScene(float width, float height)
: am(AudioManager::Instance())
, gm(GameManager(am, noteInScreen))
, sm(SettingsManager::Instance())
, note_plate(platePosition, 0)
, comboText(sf::Color(128, 128, 128, 255), width / 2, comboHeight)
, judgeText(sf::Color(128, 128, 128, 255), width / 2, judgeHeight)
, resultRectangle(width, height, font)
, screen_width(width), screen_height(height)
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

    hp_bar = new HpBar(screen_width/2+ plateWidth/2, 75, 25,375, font, 15);
}

GameScene::~GameScene() {
    free(hp_bar);
}

void GameScene::onActivate() {
	SceneManager& scene_manager = SceneManager::getInstance();
	printf("on Activate\n");
    musicStarted = false;
    
    for (int i = 0; i < 4; i++)
        processedIndex[i] = 0;

    note_speed = sm.GetNoteSpeed();
    initialize();
	setSongInfo(scene_manager.currentPlaySong, scene_manager.currentDifficultyIndex);
    gm.init(song_data);
    noteClock.restart();
}

void GameScene::initialize() {
    game_finished = false;
    finish_process = false;
    //Game Setting
    noteTravelTime = (judgeY - note_startPos_Y) / note_speed;

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
    judgeLine.setPosition(225, 440);
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
}

void GameScene::update(float dt) {
    if (!noteClockStarted) {
        noteClock.restart();
        noteClockStarted = true;
    }

    if (!musicStarted && noteClock.getElapsedTime().asSeconds() >= noteTravelTime) {
        am.PlayMusic(songInfo.songNameStr);
        musicStarted = true;
    }

    if (musicStarted && am.GetMusicStatus() == sf::Music::Stopped) {
        game_finished = true;
        if (!finish_process) {
            resultRectangle.setResult(gm.getAccuracy(), gm.getScore(), gm.getMaxCombo(), gm.getTargetPass(), false);
            am.StopMusic(songInfo.songNameStr);
            am.PlayMusic("Result");

            ResultData data(gm.getAccuracy(), gm.getScore(), gm.getMaxCombo(), gm.getTargetPass()); // 현재 결과

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

            finish_process = true;
        }

    }

    long long noteTime = noteClock.getElapsedTime().asMilliseconds();

    for (int lane = 0; lane < 4; lane++) {
        for (int i = processedIndex[lane]; i < song_data.NotePoints[lane].size(); ++i) {
            long long time = song_data.NotePoints[lane][i].first;

            if (noteTime < time) {
                break; // 시간이 아직 안됐으면 종료
            }

            int xPosition = note_startPos_X + note_distance * lane;
            sf::Color color = sf::Color::Green;
            Note note(lane, xPosition, note_startPos_Y, note_size, color, time, false);
            noteInScreen.push_back(note);
            processedIndex[lane] = i + 1;
        }
    }
    gm.checkMiss(judgeText, comboText);

    comboText.animation(dt);
    judgeText.animation(dt);

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
    if(game_finished)
        window.draw(resultRectangle);
}

Signal GameScene::handleInput(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
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
        else if (event.key.code == sf::Keyboard::Enter) {
            if (game_finished) {
                onDeactivate();
                return Signal::GoToSongMenu;
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

// hp bar object

HpBar::HpBar(float x, float y, float width, float height, sf::Font font, int font_size) {
    pos.x = x;
    pos.y = y;
    hp = 100;
    hpColor = sf::Color::Red;
    this->height = height;
    this->width = width;

    hp_height = this->height - 40;
    full_hp_height= this->height - 40;

    pannel_rect.setFillColor(sf::Color(128, 128, 128));
    pannel_rect.setSize(sf::Vector2f(width, height));
    pannel_rect.setPosition(x,y);

    hp_rect.setFillColor(sf::Color::Red);
    hp_rect.setSize(sf::Vector2f(width-10, hp_height));
    hp_y_pos = y + 30;
    hp_rect.setPosition(x+5, y+30);

    this->font = font;
    label.setFont(this->font);
    label.setString("HP");
    label.setCharacterSize(font_size);
    label.setFillColor(sf::Color::Black);
    label.setPosition(x +2, y + 10);
    label.setStyle(sf::Text::Bold);
}

void HpBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(pannel_rect, states);
    target.draw(hp_rect, states);
    target.draw(label, states);
}

void HpBar::setHP(double hp) {
    double hpHeightRate = hp / (double)100;
    hp_height = full_hp_height * hpHeightRate;
    hp_rect.setSize(sf::Vector2f(width - 10, hp_height));

    hp_y_pos = (full_hp_height - hp_height);
    hp_rect.setPosition(pos.x + 5, pos.y + 30 + hp_y_pos);
}