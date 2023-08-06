#pragma once
#include <list>

#include "AudioManager.h"
#include "parse_data.h"
#include "JudgeText.h"
#include "ComboText.h"
#include "Note.h"

class GameManager {
public:
    GameManager(AudioManager& am, std::list<Note>& noteInScreen)
        : am(am), judgeIndex(0), score(0), accuracy(0.0), combo(0), maxCombo(0), hp(100), hpUpRate(1.0), hpDownRate(1.0), rate(1.0), noteInScreen(noteInScreen) {
        keyDown.fill(false);
        targetPass.fill(0);
    }

    void keyDownProcess(int keyIndex, JudgeText& judgeText, ComboText& comboText);
    void checkMiss(JudgeText& judgeText, ComboText& comboText);

    void calAccuracy();

    void init(SongData& data);

    int getJudgeIndex() const;
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

private:
    AudioManager& am;
    SongData song_data;

    std::list<Note>& noteInScreen;

    int judgeIndex;
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
};
