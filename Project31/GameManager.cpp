#include "GameManager.h"

void GameManager::keyDownProcess(int keyIndex) {
    for (int i = judgeIndex; i < song_data.NotePoints.size(); ++i) {
        long long time = song_data.NotePoints[i].first;
        const std::array<int, 4>& lanes = song_data.NotePoints[i].second;

        long long abs_v = abs(time - am.getMusic().getPlayingOffset().asMilliseconds());

        if (abs_v > 140) break; // ���� ���� ������ ���� �ڵ�

        if (lanes[keyIndex] > 0) // ��Ʈ�� ���� ���
        {
            // ���� ó�� �� ���� ��� �ڵ� �ۼ�
            // ...

            song_data.NotePoints[i].second[keyIndex] = 0; // ��Ʈ ģ������ ǥ��
            song_data.ImagePoints[i].second[keyIndex] = 0; // Render �Լ����� �ش� ��Ʈ ǥ�� ����

            judgeIndex = i + 1; // ó���� ��Ʈ �ε��� ������Ʈ
            break;
        }
    }
}

// "Miss" ������ ó���ϴ� �޼ҵ�
void GameManager::checkMiss() {
    while (judgeIndex < song_data.NotePoints.size()) {
        long long noteTime = song_data.NotePoints[judgeIndex].first;
        const std::array<int, 4>& lanes = song_data.NotePoints[judgeIndex].second;

        if (noteTime < am.getMusic().getPlayingOffset().asMilliseconds() - 140) {
            // ���� ó�� �� ���� ��� �ڵ� �ۼ�
            // ...

            for (int i = 0; i < 4; ++i) {
                if (lanes[i] > 0) {
                    song_data.NotePoints[judgeIndex].second[i] = 0;
                    song_data.ImagePoints[judgeIndex].second[i] = 0;
                }
            }

            judgeIndex++;
        }
        else {
            break;
        }
    }
}