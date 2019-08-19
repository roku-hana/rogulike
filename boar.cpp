#include"boar.h"
#include<DxLib.h>
#include"error.h"
#include"charactersprite.h"
#include"enemymovecomponent.h"
#include"gamestage.h"
#include"player.h"

const int DRAW_PLAYER_X = 320;
const int DRAW_PLAYER_Y = 224;

Boar::Boar(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int* px, int* py, EnemyParameter ep) :
	Enemy(game, map, x, y, px, py)
{
	if (gh[0] == 0) {
		if (-1 == LoadDivGraph("Images\\Boar1.png", 24, 6, 4, 32, 32, gh)) MSG("イノシシ画像読み込みエラー");
	}

	SpriteComponent* sc = new CharacterSprite(this, 50);
	sc->SetImage(gh);

	EnemyMoveComponent* emc = new EnemyMoveComponent(this, &indexX, &indexY);

	param = ep;
	SetPosition(Vector2(-10, -10));
	dir = DOWN;
	temp = NONE;
}

Boar::~Boar() {
	
}

void Boar::updateActor() {
	int ex = indexX - *px / CHIPSIZE;
	int ey = indexY - *py / CHIPSIZE;
	Vector2 setpos = { DRAW_PLAYER_X + ex * CHIPSIZE, DRAW_PLAYER_Y + ey * CHIPSIZE };
	if (isDraw(ex, ey)) {
		if(moveflag) SetPosition(setpos);
	}
	else SetPosition(Vector2(-20, -20));

	//プレイヤーが移動したら敵の移動フラグを立てる
	if (GetGameStage()->GetPlayer()->GetMoveFlag()) moveflag = true;
	else moveflag = false;
	
	if (moveflag) {
		DefineDirection();
		AllWall();
	}

	//ダメージ = 攻撃力 - 防御力
	if(damageAmount) param.nowhp -= (damageAmount - param.defense);
	DrawFormatString(300, 30, GetColor(255, 0, 0), "hp:%d", param.nowhp);
	damageAmount = 0;

	/*	switch (dir) {
		case UP: DrawString(400, 50, "UP", GetColor(0, 0, 255)); break;
		case DOWN: DrawString(400, 70, "DOWN", GetColor(0, 0, 255)); break;
		case RIGHT: DrawString(400, 90, "RIGHT", GetColor(0, 0, 255)); break;
		case LEFT: DrawString(400, 110, "LEFT", GetColor(0, 0, 255)); break;
		case UP_RIGHT: DrawString(400, 130, "UP_RIGHT", GetColor(0, 0, 255)); break;
		case UP_LEFT: DrawString(400, 150, "UP_LEFT", GetColor(0, 0, 255)); break;
		case DOWN_RIGHT: DrawString(400, 170, "DOWN_RIGHT", GetColor(0, 0, 255)); break;
		case DOWN_LEFT: DrawString(400, 190, "DOWN_LEFT", GetColor(0, 0, 255)); break;
		}*/

	//一時的なもの(マップ上での敵の位置を表示)
	DrawBox(indexX * 5, indexY * 5, indexX * 5 + 5, indexY * 5 + 5, GetColor(0, 255, 0), TRUE);
}

void Boar::ActorInput(InputManager* input) {

}

int Boar::gh[24];