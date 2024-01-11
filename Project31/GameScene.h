#pragma once
#include "Scene.h"
#include "SongMenuScene.h"

#include "parse_data.h"
#include "Note.h"
#include "NotePlate.h"
#include "ComboText.h"
#include "JudgeText.h"
#include "ResultUI.h"

#include "GameManager.h"
#include "SettingsManager.h"
#include "playResult.h"
#include "HpBar.h"
#include "NameInputUI.h"
#include "deadPannel.h"
#include "ReadyText.h"

#include <SFML/Graphics.hpp>
#include <list>

#define NOTE_CLOCK_STARTED 0
#define FINISH_PROCESS 1
#define GAME_FINISHED 2
#define WAITED 3
#define MUSIC_STARTED 4

class GameScene : public Scene {
public:
    GameScene(float width, float height);
    ~GameScene();

    void initialize();
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;

    void onActivate();
    void onDeactivate();

    void setSongInfo(const SongInfo& songInfo, int difficultyIndex);
    void reset();

private:
    // 오디오 매니저
    AudioManager& am;
    sf::Clock noteClock;

    // 게임 매니저
    GameManager gm;

    // 사용자 세팅
    SettingsManager& sm;

    float screen_width;
    float screen_height;

    // 곡 정보
    SongInfo songInfo;
    int difficultyIndex;
    SongData song_data;

    std::string generateFilePath(const SongInfo& songInfo, int difficultyIndex);

    // notes
    std::list<Note> noteInScreen;

    // Game UI position and size value
    sf::RectangleShape buttons[4];
    bool keyPushed[4];

    float plateWidth = 400;
    float platePosition = 200;;

    ComboText comboText;
    float comboHeight = 50;
    unsigned int comboFontSize = 80;

    JudgeText judgeText;
    float judgeHeight = 300;
    unsigned int judgeFontSize = 60;

    int start_pos = 255;
    int buttonY = 500;
    int bt_distance = 80;

    sf::Vector2f accPos = sf::Vector2f(10,10);
    unsigned int accFontSize = 24;

    float scoreHeight = 10;
    sf::Vector2f scorePos = sf::Vector2f(610,10);
    unsigned int scoreFontSize = 24;

    sf::Vector2f scorePannel_outerSize = sf::Vector2f(100,100);
    sf::Vector2f scorePannel_innerSize = sf::Vector2f(50, 50);

    // note info
    int processedIndex[4] = {0,0,0,0};

    double note_speed;
    float note_size=90;
    int note_startPos_X = 220;
    int note_startPos_Y = -10;
    int note_distance = 90;

    int judgeY = 440;

    double noteTravelTime;

    // 화면 그리기에 필요한 멤버 변수들
    sf::Font font;
    sf::Text scoreText, accurateText;
    sf::RectangleShape scorePannel_outer;
    sf::RectangleShape scorePannel_inner;
    NotePlate note_plate;
    sf::RectangleShape judgeLine;
    HpBar *hp_bar;

    // game finished ui
    // Input UI
    NameInputUI input_ui;
    std::string username;

    // Result UI
    ResultUI resultRectangle;

    // died UI
    DeadPannel deadPannel;

    // ready UI
    ReadyText ready_txt;

    //states
    uint8_t input_process;
    // 0 : noteClockStarted;
    // 1 : finish_process
    // 2 : game_finished 
    // 3 : wiat count
    // 4 : musicStarted
    uint8_t music_note_process;
    uint8_t count_factor;

    bool isAlive;
    double hp;
};