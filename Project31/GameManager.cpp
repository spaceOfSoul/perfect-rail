#include "GameManager.h"

void GameManager::calAccuracy() {
    int totalJudgedNotes = targetPass[1] + targetPass[2] + targetPass[3] + targetPass[4] + targetPass[0];
    if (totalJudgedNotes == 0) { // �������� ��Ʈ�� ������ ��Ȯ���� 0
        accuracy = 0.0;
    }
    else {
        accuracy = ((35.0 * targetPass[1] + 65.0 * targetPass[2] + 100.0 * (targetPass[3] + targetPass[4])) /
            (totalJudgedNotes));
    }
}

void GameManager::removeNote(int selected_time) {
    for (std::list<Note>::iterator iter = noteInScreen.begin(); iter != noteInScreen.end(); ) {
        if (iter->time == selected_time) {
            iter = noteInScreen.erase(iter);
            break;
        }
        else {
            ++iter;
        }
    }
}

void GameManager::keyDownProcess(int keyIndex, JudgeText& judgeText, ComboText& comboText) {
    //printf("pushed\n");
    for (int i = judgeIndex[keyIndex]; i < song_data.NotePoints[keyIndex].size(); ++i) {
        int time = song_data.NotePoints[keyIndex][i].first;

        int abs_v = abs(time - am.getMusic().getPlayingOffset().asMilliseconds());

        //printf("key : %d judge executed\n", keyIndex);
        if (abs_v <= 25) { //kool ����
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
            removeNote(time);

            song_data.NotePoints[keyIndex][i].second = 0; //��Ʈ ģ������ ǥ��
            song_data.ImagePoints[keyIndex][i].second = 0; //�ճ�Ʈ�� �ϴ� ����

            judgeIndex[keyIndex] = i + 1;
            break;
        }
        else if (abs_v <= 41.3) { //cool ����
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
            removeNote(time);

            song_data.NotePoints[keyIndex][i].second = 0; //��Ʈ ģ������ ǥ��
            song_data.ImagePoints[keyIndex][i].second = 0; //�ճ�Ʈ�� �ϴ� ����

            judgeIndex[keyIndex] = i + 1;
            break;
        }
        else if (abs_v <= 78.5) { //good ����
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
            removeNote(time);

            song_data.NotePoints[keyIndex][i].second = 0; //��Ʈ ģ������ ǥ��
            song_data.ImagePoints[keyIndex][i].second = 0; //�ճ�Ʈ�� �ϴ� ����

            judgeIndex[keyIndex] = i + 1;
            break;
        }
        else if (abs_v < 120) {//bad ����
            targetPass[1]++;  //bad
            lastJudge = 1; //bad
            combo++;
            if (combo >= maxCombo)
                maxCombo = combo;
            hp -=3;
            hpDownRate *= 1.1;
            score += 15 * rate;

            judgeText.setJudgement(1);
            comboText.setCombo(combo);
            calAccuracy();
            removeNote(time);

            song_data.NotePoints[keyIndex][i].second = 0; //��Ʈ ģ������ ǥ��
            song_data.ImagePoints[keyIndex][i].second = 0; //�ճ�Ʈ�� �ϴ� ����

            judgeIndex[keyIndex] = i + 1;
            break;
        }else if(120 <= abs_v && abs_v <= 170) { // miss
            targetPass[0]++;// miss
            lastJudge = 0;
            combo = 0;
            hp -= 10 * hpDownRate;
            hpDownRate *= 1.2;
            hpUpRate = 1.0;

            judgeText.setJudgement(0);
            comboText.setCombo(combo);
            calAccuracy();
            removeNote(time);

            song_data.NotePoints[keyIndex][i].second = 0; //��Ʈ ģ������ ǥ��
            song_data.ImagePoints[keyIndex][i].second = 0; //�ճ�Ʈ�� �ϴ� ����

            judgeIndex[keyIndex] = i + 1;
            break;
        }
        else
        break;
    }
}

// Miss ����
void GameManager::checkMiss(JudgeText& judgeText, ComboText& comboText) {
    for (int keyIndex = 0; keyIndex < 4; keyIndex++) {
        while (judgeIndex[keyIndex] < song_data.NotePoints[keyIndex].size()) {
            long long noteTime = song_data.NotePoints[keyIndex][judgeIndex[keyIndex]].first;

            if (noteTime < am.getMusic().getPlayingOffset().asMilliseconds() - 120) {
                   targetPass[0]++; // MISS ����
                   lastJudge = 0;
                   combo = 0;
                   hp -= 10 * hpDownRate; //hp ����
                   hpDownRate *= 1.2; //hp ���� ����ġ ����
                   hpUpRate = 1.0; //hp ��� ����ġ 

                   song_data.NotePoints[keyIndex][judgeIndex[keyIndex]].second = 0; // ��Ʈ ����
                   song_data.ImagePoints[keyIndex][judgeIndex[keyIndex]].second = 0;
                   judgeText.setJudgement(0);
                   comboText.setCombo(combo);
                   calAccuracy();
                   judgeIndex[keyIndex]++;
            }
            else
                break;
        }
    }
}

void GameManager::init(SongData& data) {
    song_data = data;

    for(int i=0; i<4; i++)
        judgeIndex[i] = 0;

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
