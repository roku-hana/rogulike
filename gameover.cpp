#include"gameover.h"
#include"title.h"
#include<DxLib.h>
#include"soundbox.h"
#include"input.h"
#include"gamestage.h"

GameOver::GameOver(Game* pManager, SceneManager* sManager) :
	GameScene(pManager, sManager) {
	count = 0;
	BigFont = CreateFontToHandle(NULL, 50, 10);
}

void GameOver::update() {
	if (count <= 0) {
		SoundBox::playSound(5);
		SoundBox::stopSound(1);
	}
	count++;
	if (gameManager->input->isPushB()) {
		//savePlayerInfo(5, 1, gameStage->getDeathCount());	
		sceneManager->scene = new Title(sceneManager);
		delete gameManager;
	}
}

void GameOver::draw() {
	if (count <= 300) DrawStringToHandle(200, 200, "GAMEOVER", GetColor(255, 0, 0), BigFont);
	else DrawResult();
}

void GameOver::DrawResult() {
	DrawString(270, 100, "–`Œ¯‚ÌŒ‹‰Ê", GetColor(255, 255, 255));
	DrawString(200, 150, GameStage::ri.plname.c_str(), GetColor(255, 255, 0));
	DrawFormatString(200 + GameStage::ri.plname.size() * 10, 150, GetColor(255, 255, 255) ,"‚Í’n‰º%dŠK‚É‚Ä", GameStage::stageNum);
	DrawString(200, 200, GameStage::ri.enname.c_str(), GetColor(255, 255, 0));
	DrawString(200 + GameStage::ri.enname.size() * 10, 200, "‚É“|‚³‚ê‚½", GetColor(255, 255, 255));
	DrawString(100, 250, "ƒŒƒxƒ‹", GetColor(255, 255, 255));
	DrawFormatString(170, 250, GetColor(0, 0, 255), "%d", GameStage::ri.level);
	DrawString(100, 300, "HP", GetColor(255, 255, 255));
	DrawFormatString(170, 300, GetColor(0, 0, 255), "%d", GameStage::ri.hp);
	DrawString(100, 350, "‚Ð‚æ‚±", GetColor(255, 255, 255));
	DrawFormatString(170, 350, GetColor(0, 0, 255), "%d", GameStage::ri.chickNum);
	DrawString(450, 250, "•Ší", GetColor(255, 255, 255));
	DrawFormatString(520, 250, GetColor(0, 0, 255), GameStage::ri.weapon.c_str());
	DrawString(450, 300, "–h‹ï", GetColor(255, 255, 255));
	DrawString(520, 300, GameStage::ri.protection.c_str(), GetColor(0, 0, 255));
	DrawString(450, 350, "ŒoŒ±’l", GetColor(255, 255, 255));
	DrawFormatString(520, 350, GetColor(0, 0, 255), "%d", GameStage::ri.experience);
}