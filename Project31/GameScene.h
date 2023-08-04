#pragma once
#include "Scene.h"
#include "SongMenuScene.h"

#include "parse_data.h"
#include "Note.h"

#include <SFML/Graphics.hpp>
#include <list>

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
    sf::Clock musicStartClock;

    bool musicStarted;

    // 곡 정보
    SongInfo songInfo;
    int difficultyIndex;
    SongData song_data;

    std::string generateFilePath(const SongInfo& songInfo, int difficultyIndex);

    // notes
    std::list<Note> noteInScreen;

    // UI position and size value
    sf::RectangleShape buttons[4];
    bool keyPushed[4];

    float plateWidth = 400;
    float platePosition = 200;;

    float comboHeight = 100;
    unsigned int comboFontSize = 60;

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
    int processedIndex = 0;

    float note_speed = 800;
    int note_startPos = 230;
    int note_distance = 90;

    // 화면 그리기에 필요한 멤버 변수들
    sf::Font font;
    sf::RectangleShape plate;
    sf::RectangleShape notePlace;
    sf::Text comboText, scoreText, accurateText;
    sf::RectangleShape scorePannel_outer;
    sf::RectangleShape scorePannel_inner;
};
