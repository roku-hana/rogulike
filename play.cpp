#include"play.h"
#include"input.h"
#include<DxLib.h>
#include"pause.h"
#include"soundbox.h"
#include"gamestage.h"
#include"nextstage.h"
#include"gameover.h"
#include"player.h"

Play::Play(Game* pManager, SceneManager* sManager) :
	GameScene(pManager, sManager) {
	gamestage = pManager->getGameStage();
	cur.x = 415;
	cur.y = 65;
	cur.r = 2;
	cur.pos = 0;
}

void Play::update() {
	SoundBox::playBgm(1);
	//gamestage->ProcessInput();
	gamestage->update();
	gamestage->ProcessInput();
	if (gamestage->NextStage()) {
		if (gameManager->input->isPushUp() && cur.pos > 0) {
			cur.y -= 20;
			cur.pos--;
		}
		if (gameManager->input->isPushDown() && cur.pos < 1) {
			cur.y += 20;
			cur.pos++;
		}
		if (gameManager->input->isPushB(0) == 1) {
			if (cur.pos == 0) {
				gamestage->GetPlayer()->SetActState(KEY_INPUT);
				GameStage::stageNum++;
				sceneManager->scene = new NextStage(sceneManager, gamestage->NextStage());
				delete this;
			}
			else if (cur.pos == 1) gamestage->GetPlayer()->SetActState(KEY_INPUT);
		}
	}
	else if (gameManager->input->isPushBack(0) == 1) {
		gameManager->gameScene = new Pause(gameManager, sceneManager);
		delete this;
	}
	else if (gamestage->GetGameOverFlag()) {
		gameManager->gameScene = new GameOver(gameManager, sceneManager);
		delete this;
	}
}

void Play::draw() {
	gamestage->draw();
	if (gamestage->NextStage() && gamestage->GetPlayer()->GetActState() == WAIT) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(100, 50, 400, 100, GetColor(0, 0, 51), TRUE);
		DrawBox(410, 50, 470, 100, GetColor(0, 0, 51), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(100, 50, 400, 100, GetColor(255, 255, 255), FALSE);
		DrawBox(410, 50, 470, 100, GetColor(255, 255, 255), FALSE);
		DrawString(105, 55, "äKíiÇ™Ç†ÇÈÅBéüÇÃäKÇ÷à⁄ìÆÇµÇ‹Ç∑Ç©ÅH", GetColor(255, 255, 255));
		DrawString(420, 60, "ÇÕÇ¢", GetColor(255, 255, 255));
		DrawString(420, 80, "Ç¢Ç¢Ç¶", GetColor(255, 255, 255));
		DrawCircle(cur.x, cur.y, cur.r, GetColor(255, 255, 255), TRUE);
	}
}
