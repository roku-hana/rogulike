#include"gameover.h"
#include"title.h"
#include<DxLib.h>
#include"soundbox.h"

GameOver::GameOver(Game* pManager, SceneManager* sManager) :
	GameScene(pManager, sManager) {
	count = 0;
	BigFont = CreateFontToHandle(NULL, 50, 10);
}

void GameOver::update() {
	SoundBox::playBgm(5);
	if (count <= 300) count++;
	else {
		//savePlayerInfo(5, 1, gameStage->getDeathCount());	
		sceneManager->scene = new Title(sceneManager);
		delete gameManager;
	}
}

void GameOver::draw() {
	DrawStringToHandle(200, 200, "GAMEOVER", GetColor(255, 0, 0), BigFont);
}