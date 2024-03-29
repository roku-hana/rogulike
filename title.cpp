#include"title.h"
#include<DxLib.h>
#include"input.h"
#include"game.h"
#include"soundbox.h"

Title::Title(SceneManager* pt) : Scene(pt) {
	back = LoadGraph("Images\\title.png");
}

void Title::update() {
	SoundBox::playBgm(0);
	if (sceneManager->input->isPushB()) {
		sceneManager->scene = new Game(sceneManager, sceneManager->input);
		delete this;
	}
}

void Title::draw() {
	DrawGraph(0, 0, back, TRUE);
	DrawString(0, 50, "StartorXキー:ゲーム画面に移動", GetColor(0, 0, 0));
}