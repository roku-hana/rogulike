#include"play.h"
#include"input.h"
#include<DxLib.h>
#include"pause.h"
#include"soundbox.h"
#include"gamestage.h"
#include"nextstage.h"

Play::Play(Game* pManager, SceneManager* sManager) :
	GameScene(pManager, sManager) {
	//back = LoadGraph("Images\\play.png");
	gamestage = pManager->getGameStage();
}

void Play::update() {
	SoundBox::playBgm(1);
	gamestage->update();
	gamestage->ProcessInput();
	if (gamestage->NextStage()) {

		//��ŁA�����ύX
		DrawString(150, 300, "X�{�^���������āA���̊K�ֈړ�", GetColor(255, 255, 255));
		if (gameManager->input->isPushX(0) == 1) {
			sceneManager->scene = new NextStage(sceneManager, gamestage->NextStage());
			delete this;
		}
	}
	else if (gameManager->input->isPushStart(0) == 1) {
		gameManager->gameScene = new Pause(gameManager, sceneManager);
		delete this;
	}
}

void Play::draw() {
	//DrawGraph(0, 0, back, TRUE);
	DrawString(0, 50, "Start or X�L�[:PAUSE��ʂɈړ�", GetColor(255, 255, 255));
	gamestage->draw();
	
}
