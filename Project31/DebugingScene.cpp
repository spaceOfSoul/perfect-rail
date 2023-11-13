#include "DebugingScene.h"

DebuggingScene::DebuggingScene(float width, float height) : dead_ui(0,0) {
	this->width = width;
	this->height = height;
}

DebuggingScene::~DebuggingScene() {

}


void DebuggingScene::update(float dt) {
	// ±¸ÇöºÎ
}

void DebuggingScene::onActivate() {

}

void DebuggingScene::onDeactivate() {

}

void DebuggingScene::draw(sf::RenderWindow& window) {
	window.draw(dead_ui);
}

Signal DebuggingScene::handleInput(sf::Event event, sf::RenderWindow& window) {
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			return Signal::GoToMainMenu;
	}
	return Signal::None;
}
