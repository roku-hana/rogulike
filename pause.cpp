#include"pause.h"
#include<DxLib.h>
#include"input.h"
#include"play.h"
#include"title.h"
#include"soundbox.h"

Pause::Pause(Game* pManager, SceneManager* sManager) :
	GameScene(pManager, sManager) {
	back = LoadGraph("Images\\pause.png");
}

void Pause::update() {
	SoundBox::playBgm(1);
	if (gameManager->input->isPushA()) {
		gameManager->gameScene = new Play(gameManager, sceneManager);
		delete this;
	}
	else if (gameManager->input->isPushY()) {
		sceneManager->scene = new Title(sceneManager);
		delete gameManager;
	}
}

void Pause::draw() {
	DrawGraph(0, 0, back, TRUE);
	DrawString(0, 50, "AorZキー:プレイ画面に戻る", GetColor(0, 0, 0));
	DrawString(0, 100, "YorAキー:タイトル画面に戻る", GetColor(0, 0, 0));
}