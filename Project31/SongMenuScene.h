#pragma once
#include "Scene.h"
#include "AudioManager.h"
#include "SongInfo.h"
#include "SceneManager.h"

#include "AlbumArt.h"

#include "scoresPannel.h"
#include "playResult.h"

#include <filesystem>
#include <vector>
#include <stdio.h>
#include <map>

class SongMenuScene : public Scene {
private:
    sf::Font font;

    AudioManager& am;

    std::vector<SongInfo> songInfos;
    std::map<std::string, ResultData> song_results;
    std::unique_ptr<AlbumArt> albumImage;
    std::unique_ptr<HighscorePannel> region_highscore;
    int selectedItemIndex = 0;
    int selectedDifficultyIndex = 0;

    float width;
    float height;

public:
    SongMenuScene(float width, float height);
    ~SongMenuScene();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    Signal handleInput(sf::Event event, sf::RenderWindow& window) override;
    
    void onActivate();
    void onDeactivate();

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

    int GetPressedItem() { return selectedItemIndex; }
};
