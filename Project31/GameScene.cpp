#include "GameScene.h"

GameScene::GameScene(float width, float height) {

}

GameScene::~GameScene() {

}

void GameScene::onActivate() {
	SceneManager& scene_manager = SceneManager::getInstance();
	printf("on Activate\n");
	setSongInfo(scene_manager.currentPlaySong, scene_manager.currentDifficultyIndex);
}

void GameScene::update(float dt) {

}

void GameScene::onDeactivate() {

}

void GameScene::draw(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("fonts\\arial.ttf")) {
        // ���� ó��
    }

    // ���̾ƿ�

    // Plate rectangle
    sf::RectangleShape plate(sf::Vector2f(400, 600));
    plate.setFillColor(sf::Color::White);
    plate.setPosition(200, 0);
    window.draw(plate);

    // note place
    sf::RectangleShape notePlace(sf::Vector2f(350, 475));
    notePlace.setFillColor(sf::Color::Black);
    notePlace.setPosition(225, 0);
    window.draw(notePlace);

    // �޺�, ���ھ�, ��Ȯ�� ǥ�ø� ���� �ؽ�Ʈ ��ü
    sf::Text comboText, scoreText, accurateText;
    comboText.setFont(font);
    scoreText.setFont(font);
    accurateText.setFont(font);

    // �޺� ǥ��
    int Combo = 24; // TEST

    if (Combo > 0) { // �޺��� 0 �̻��ϰ��
        comboText.setString(std::to_string(Combo));
        comboText.setCharacterSize(50); // 24�ȼ�
        comboText.setFillColor(sf::Color(128, 128, 128)); // ȸ������ ����
        comboText.setPosition(10, 110);
        window.draw(comboText);
    }

    // ���ھ� ǥ��
    int Score = 1000; // TEST
    
    scoreText.setString(std::to_string(Score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(128, 128, 128));
    scoreText.setPosition(10, 10);
    window.draw(scoreText);

    // ��Ȯ�� ǥ��
    float Accurate = 98.f; // TEST

    accurateText.setString(std::to_string(Accurate) + "%");
    accurateText.setCharacterSize(24);
    accurateText.setFillColor(sf::Color(128, 128, 128));
    accurateText.setPosition(10, 40);
    window.draw(accurateText);
}

Signal GameScene::handleInput(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            return Signal::GoToSongMenu;
        }
    }

    // input effect
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        printf("D key is being pressed\n");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        printf("F key is being pressed\n");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        printf("J key is being pressed\n");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        printf("K key is being pressed\n");
    }


	return Signal::None;
}

void reset() {

}

std::string GameScene::generateFilePath(const SongInfo& songInfo, int difficultyIndex) {
	std::string difficulties[3] = { "Normal", "Hard", "Expert" };
	std::string filePath = "Songs/" + songInfo.songNameStr + "/" + difficulties[songInfo.difficultiesExist[difficultyIndex]] + ".osu";
	return filePath;
}

void GameScene::setSongInfo(const SongInfo &songInfo, int difficulty) {
	this->songInfo = songInfo;
	this->difficultyIndex = difficulty;

	//file path
	std::string filePath = generateFilePath(songInfo, difficultyIndex);
	printf("Load %s\n", filePath.c_str());

	LoadMapFile(filePath, song_data);
}