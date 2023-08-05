#pragma once
#include "AudioManager.h"
#include "parse_data.h"

class GameManager {
public:
    GameManager(AudioManager& am)
        : am(am), judgeIndex(0), score(0), accuracy(0.0), combo(0), maxCombo(0), hp(100), hpUpRate(1.0), hpDownRate(1.0), rate(1.0) {
        keyDown.fill(false);
        targetPass.fill(0);
    }

    void keyDownProcess(int keyIndex);
    void checkMiss();
    // ... (다른 메소드들)

private:
    AudioManager& am;
    int judgeIndex;
    SongData song_data;

    int score;
    double accuracy;
    std::array<bool, 4> keyDown;
    std::array<int, 5> targetPass; // MISS, BAD, GOOD, COOL, KOOL
    int lastPan;
    int panVisualTimer;
    int combo;
    int maxCombo;
    double hp;
    double hpUpRate;
    double hpDownRate;
    double rate;
};
