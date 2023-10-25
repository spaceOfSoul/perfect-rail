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

#include <SFML/Graphics.hpp>
#include <list>

class HpBar : public sf::Drawable {
public:
    HpBar(float x, float y, float width, float height, sf::Font font, int font_size);
    void setHP(double hp);
private:
    sf::Vector2f pos;
    double hp;
    sf::Color hpColor;
    float full_hp_height;
    float hp_height;
    float hp_y_pos;
    float height;
    float width;
    sf::Font font;

    //render objs
    sf::RectangleShape pannel_rect;
    sf::RectangleShape hp_rect;
    sf::Text label;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

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
    // ����� �Ŵ���
    AudioManager& am;
    sf::Clock noteClock;

    // ���� �Ŵ���
    GameManager gm;

    // ����� ����
    SettingsManager& sm;

    float screen_width;
    float screen_height;

    bool musicStarted;
    bool noteClockStarted;

    // �� ����
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

    // hp bar
    HpBar* hp_bar;

    // note info
    int processedIndex[4] = {0,0,0,0};

    double note_speed;
    float note_size=90;
    int note_startPos_X = 220;
    int note_startPos_Y = -10;
    int note_distance = 90;

    int judgeY = 440;

    double noteTravelTime;

    // ȭ�� �׸��⿡ �ʿ��� ��� ������
    sf::Font font;
    sf::Text scoreText, accurateText;
    sf::RectangleShape scorePannel_outer;
    sf::RectangleShape scorePannel_inner;
    NotePlate note_plate;
    sf::RectangleShape judgeLine;

    // Result UI
    bool game_finished = false;
    ResultUI resultRectangle;

    bool finish_process;
};