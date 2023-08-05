#include "GameManager.h"

void GameManager::calAccuracy() {
    int totalJudgedNotes = targetPass[1] + targetPass[2] + targetPass[3] + targetPass[4];
    if (totalJudgedNotes == 0) { // 판정받은 노트가 없으면 정확도는 0
        accuracy = 0.0;
    }
    else {
        accuracy = ((70.0 * targetPass[1] + 130.0 * targetPass[2] + 200.0 * (targetPass[3] + targetPass[4])) /
            (totalJudgedNotes * 2.0)) * 100;
    }
}

void GameManager::keyDownProcess(int keyIndex, JudgeText& judgeText, ComboText& comboText) {
    for (int i = judgeIndex; i < song_data.NotePoints.size(); ++i) {
        long long time = song_data.NotePoints[i].first;
        const std::array<int, 4>& lanes = song_data.NotePoints[i].second;

        long long abs_v = abs(time - am.getMusic().getPlayingOffset().asMilliseconds());

        if (abs_v <= 22) { //kool 범위
            targetPass[4]++; //kool
            lastJudge = 4; //kool
            combo++;
            if (combo >= maxCombo)
                maxCombo = combo;
            if (hp + (2.5 * hpUpRate) <= 100)
                hp += (2.5 * hpUpRate);
            else
                hp = 100;
            hpUpRate *= 1.15;
            hpDownRate = 1.0;
            score += 55 * rate;

            judgeText.setJudgement(4);
            comboText.setCombo(combo);
            calAccuracy();

            song_data.NotePoints[i].second[keyIndex] = 0; //노트 친것으로 표시
            song_data.ImagePoints[i].second[keyIndex] = 0; //롱노트는 일단 보류

            judgeIndex = i + 1;
            break;
        }
        else if (abs_v <= 40.5) { //cool 범위
            targetPass[3]++;  //cool
            lastJudge = 3; //cool
            combo++;
            if (combo >= maxCombo)
                maxCombo = combo;
            if (hp + (2 * hpUpRate) <= 100)
                hp += (2 * hpUpRate);
            else
                hp = 100;
            hpUpRate *= 1.1;
            hpDownRate = 1.0;
            score += 50 * rate;

            judgeText.setJudgement(3);
            comboText.setCombo(combo);
            calAccuracy();

            song_data.NotePoints[i].second[keyIndex] = 0; //노트 친것으로 표시
            song_data.ImagePoints[i].second[keyIndex] = 0; //롱노트는 일단 보류

            judgeIndex = i + 1;
            break;
        }
        else if (abs_v <= 73.5) { //good 범위
            targetPass[2]++;  //good
            lastJudge = 2; //good
            combo++;
            if (combo >= maxCombo)
                maxCombo = combo;
            if (hp + (1 * hpUpRate) <= 100)
                hp += (1 * hpUpRate);
            else
                hp = 100;
            hpUpRate *= 1.05;
            hpDownRate = 1.0;
            score += 35 * rate;

            judgeText.setJudgement(2);
            comboText.setCombo(combo);
            calAccuracy();

            song_data.NotePoints[i].second[keyIndex] = 0; //노트 친것으로 표시
            song_data.ImagePoints[i].second[keyIndex] = 0; //롱노트는 일단 보류

            judgeIndex = i + 1;
            break;
        }
        else if (abs_v > 130 && abs_v < 170) {// miss
            targetPass[0]++;// miss
            lastJudge = 0;
            combo = 0;
            hp -= 3 * hpDownRate;
            hpDownRate *= 1.1;
            hpUpRate = 1.0;

            judgeText.setJudgement(0);
            comboText.setCombo(combo);
            calAccuracy();

            song_data.NotePoints[i].second[keyIndex] = 0; //노트 친것으로 표시
            song_data.ImagePoints[i].second[keyIndex] = 0; //롱노트는 일단 보류

            judgeIndex = i + 1;
            break;
        }else{ //bad 범위
            targetPass[1]++;  //bad
            lastJudge = 1; //bad
            combo++;
            if (combo >= maxCombo)
                maxCombo = combo;
            hp--;
            hpDownRate *= 1.1;
            score += 15 * rate;

            judgeText.setJudgement(1);
            comboText.setCombo(combo);
            calAccuracy();

            song_data.NotePoints[i].second[keyIndex] = 0; //노트 친것으로 표시
            song_data.ImagePoints[i].second[keyIndex] = 0; //롱노트는 일단 보류

            judgeIndex = i + 1;
            break;
        }
    }
}

// Miss 판정
void GameManager::checkMiss(JudgeText& judgeText, ComboText& comboText) {
    while (judgeIndex < song_data.NotePoints.size()) {
        long long noteTime = song_data.NotePoints[judgeIndex].first;
        const std::array<int, 4>& lanes = song_data.NotePoints[judgeIndex].second;

        if (noteTime < am.getMusic().getPlayingOffset().asMilliseconds() - 130) {
            for (int i = 0; i < 4; ++i) {
                if (lanes[i] > 0) {
                    targetPass[0]++; // MISS 증가
                    lastJudge = 0;
                    combo = 0;
                    hp -= 3 * hpDownRate; //hp 차감
                    hpDownRate *= 1.1; //hp 감소 가중치 증가
                    hpUpRate = 1.0; //hp 상승 가중치 

                    song_data.NotePoints[judgeIndex].second[i] = 0; // 노트 삭제
                    song_data.ImagePoints[judgeIndex].second[i] = 0;
                    judgeText.setJudgement(0);
                    comboText.setCombo(combo);
                    calAccuracy();
                }
            }

            judgeIndex++;
        }
        else 
            break;
    }
}

void GameManager::init(SongData& data) {
    song_data = data;
    judgeIndex = 0;
    score = 0;
    accuracy = 100.0;
    combo = 0;
    maxCombo = 0;
    hp = 100;
    hpUpRate = 1.0;
    hpDownRate = 1.0;
    rate = 1.0;
    keyDown.fill(false);
    targetPass.fill(0);
}

int GameManager::getJudgeIndex() const {
    return judgeIndex;
}

int GameManager::getScore() const {
    return score;
}

double GameManager::getAccuracy() const {
    return accuracy;
}

std::array<int, 5> GameManager::getTargetPass() const {
    return targetPass;
}

int GameManager::getLastJudge() const {
    return lastJudge;
}

int GameManager::getCombo() const {
    return combo;
}

int GameManager::getMaxCombo() const {
    return maxCombo;
}

double GameManager::getHP() const {
    return hp;
}

double GameManager::getHPUpRate() const {
    return hpUpRate;
}

double GameManager::getHPDownRate() const {
    return hpDownRate;
}

double GameManager::getRate() const {
    return rate;
}
