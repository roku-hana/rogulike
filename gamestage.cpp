#include"gamestage.h"
#include"makedungeon.h"

GameStage::GameStage() {
	mp = new MapData();
}

GameStage::~GameStage() {
	delete mp;
}

void GameStage::update() {

}

void GameStage::draw() {
	mp->draw();
}