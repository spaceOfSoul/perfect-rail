#include "GameManager.h"

void GameManager::keyDownProcess(int keyIndex) {
    for (int i = judgeIndex; i < song_data.NotePoints.size(); ++i) {
        long long time = song_data.NotePoints[i].first;
        const std::array<int, 4>& lanes = song_data.NotePoints[i].second;

        long long abs_v = abs(time - am.getMusic().getPlayingOffset().asMilliseconds());

        if (abs_v > 140) break; // 판정 범위 규정을 위한 코드

        if (lanes[keyIndex] > 0) // 노트가 있을 경우
        {
            // 판정 처리 및 점수 계산 코드 작성
            // ...

            song_data.NotePoints[i].second[keyIndex] = 0; // 노트 친것으로 표시
            song_data.ImagePoints[i].second[keyIndex] = 0; // Render 함수에서 해당 노트 표시 안함

            judgeIndex = i + 1; // 처리한 노트 인덱스 업데이트
            break;
        }
    }
}

// "Miss" 판정을 처리하는 메소드
void GameManager::checkMiss() {
    while (judgeIndex < song_data.NotePoints.size()) {
        long long noteTime = song_data.NotePoints[judgeIndex].first;
        const std::array<int, 4>& lanes = song_data.NotePoints[judgeIndex].second;

        if (noteTime < am.getMusic().getPlayingOffset().asMilliseconds() - 140) {
            // 판정 처리 및 점수 계산 코드 작성
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