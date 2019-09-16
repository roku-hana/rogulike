#include"chick.h"
#include<DxLib.h>
#include"error.h"
#include"charactersprite.h"
#include"gamestage.h"
#include"movecomponent.h"
#include"player.h"

const int CHIPSIZE = 32;
const int DRAW_CHIPNUM_X = 7;
const int DRAW_CHIPNUM_Y = 6;
const int DRAW_PLAYER_X = 320;
const int DRAW_PLAYER_Y = 224;

Chick::Chick(GameStage* game, int x, int y, int* px, int* py) : Actor(game), px(px), py(py){
	if (gh[0] == 0) {
		if (-1 == LoadDivGraph("Images\\Chick1.png", 24, 6, 4, 24, 20, gh)) MSG("プレイヤー画像読み込みエラー");
		game->SetChickGraphic(gh[0]);
	}
	//game->SetChickGraphic(gh[0]);

	SpriteComponent* sc = new CharacterSprite(this, 50);
	sc->SetImage(gh);

	MoveComponent* mc = new MoveComponent(this);

	game->AddChick(this);

	indexX = x;
	indexY = y;

	SetPosition(Vector2(-10, -10));
	dir = DOWN;
	player = false;
}

Chick::~Chick() {
	GetGameStage()->RemoveChick(this);
};

void Chick::updateActor() {
	int cx = indexX - *px / CHIPSIZE;
	int cy = indexY - *py / CHIPSIZE;
	if (!moveflag) {
		if (isDraw(cx, cy)) SetPosition(Vector2(DRAW_PLAYER_X + cx * CHIPSIZE, DRAW_PLAYER_Y + cy * CHIPSIZE));
		else SetPosition(Vector2(-20, -20));
	}
	else {
		if (!player) { GetGameStage()->GetPlayer()->AddChickNum(); player = true; }
		dir = GetGameStage()->GetPlayer()->GetDirection();
	}
}

void Chick::ActorInput(InputManager* input) {

}

bool Chick::isDraw(int cx, int cy) {

	if (cx >= -1 * DRAW_CHIPNUM_X && cx <= DRAW_CHIPNUM_X) {
		if (cy >= -1 * DRAW_CHIPNUM_Y && cy <= DRAW_CHIPNUM_Y) {
			return true;
		}
	}
	return false;
}

int Chick::gh[24];