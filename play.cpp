#include"play.h"
#include"input.h"
#include<DxLib.h>
#include"pause.h"
#include"soundbox.h"
#include"gamestage.h"

Play::Play(Game* pManager, SceneManager* sManager) :
	GameScene(pManager, sManager) {
	back = LoadGraph("Images\\play.png");
	gamestage = pManager->getGameStage();
}

void Play::update() {
	SoundBox::playBgm(1);
	gamestage->update();
	gamestage->ProcessInput();
	if (gameManager->input->isPushStart(0) == 1) {
		gameManager->gameScene = new Pause(gameManager, sceneManager);
		delete this;
	}
}

void Play::draw() {
	DrawGraph(0, 0, back, TRUE);
	DrawString(0, 50, "Start or XƒL[:PAUSE‰æ–Ê‚ÉˆÚ“®", GetColor(0, 0, 0));
	gamestage->draw();
	
}
