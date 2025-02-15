#pragma once
#include <list>

#include "AudioManager.h"
#include "parse_data.h"
#include "JudgeText.h"
#include "ComboText.h"
#include "Note.h"
#include "HpBar.h"

class GameManager {
public:
    GameManager(AudioManager& am, std::list<Note>& noteInScreen)
        : am(am), judgeIndex{0,0,0,0}, score(0), accuracy(0.0), combo(0), maxCombo(0), hp(100), hpUpRate(1.0), hpDownRate(1.0), rate(1.0), noteInScreen(noteInScreen) {
        keyDown.fill(false);
        targetPass.fill(0);
    }

    void keyDownProcess(int keyIndex, JudgeText& judgeText, ComboText& comboText, uint8_t& lightIndex, uint8_t& fasl_state);
    void checkMiss(JudgeText& judgeText, ComboText& comboText);

    void calAccuracy();

    void init(SongData& data);

    double getAccuracy() const;
    std::array<int, 5> getTargetPass() const;
    int getLastJudge() const;
    double getHP() const;
    double getHPUpRate() const;
    double getHPDownRate() const;
    double getRate() const;
    int getScore() const;
    int getCombo() const;
    int getMaxCombo() const;

    void removeNote(int selected_time);

    // UI
    //HpBar* hp_bar;
private:
    AudioManager& am;
    SongData song_data;

    std::list<Note>& noteInScreen;

    int judgeIndex[4];
    int score;
    double accuracy;
    std::array<bool, 4> keyDown;
    std::array<int, 5> targetPass; // MISS, BAD, GOOD, COOL, KOOL
    int lastJudge;
    int combo;
    int maxCombo;
    double hp;
    double hpUpRate;
    double hpDownRate;
    double rate;

    const double judge_range[4] = {25,41.3, 78.5, 120};

    inline double bad_constant() { return 3; }
    inline double miss_constant() { return 6; }
};
