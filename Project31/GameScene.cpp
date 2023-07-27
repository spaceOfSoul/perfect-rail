#include "GameScene.h"

GameScene::GameScene(float width, float height) {

}

GameScene::~GameScene() {

}

void GameScene::onActivate() {
	SceneManager& scene_manager = SceneManager::getInstance();
	songInfo = scene_manager.currentPlaySong;
	difficultyIndex = scene_manager.currentDifficultyIndex;


}

void GameScene::update(float dt) {

}

void GameScene::onDeactivate() {

}

void GameScene::draw(sf::RenderWindow& window) {

}

Signal GameScene::handleInput(sf::Event event, sf::RenderWindow& window) {
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
	printf("filePath\n");
}