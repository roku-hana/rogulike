#include"boar.h"
#include<DxLib.h>
#include"error.h"
#include"charactersprite.h"
#include"enemymovecomponent.h"
#include"gamestage.h"
#include"player.h"
#include"makedungeon.h"

const int DRAW_PLAYER_X = 320;
const int DRAW_PLAYER_Y = 224;

Boar::Boar(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int* px, int* py) :
	Actor(game), mapdata(map),
	px(px),py(py),indexX(x), indexY(y)
{
	if (gh[0] == 0) {
		if (-1 == LoadDivGraph("Images\\Boar1.png", 24, 6, 4, 32, 32, gh)) MSG("イノシシ画像読み込みエラー");
	}

	SpriteComponent* sc = new CharacterSprite(this, 50);
	sc->SetImage(gh);

	EnemyMoveComponent* emc = new EnemyMoveComponent(this, &indexX, &indexY);

	game->AddEnemy(this);

	SetPosition(Vector2(-10, -10));
	dir = DOWN;
	temp = NONE;
}

Boar::~Boar() {
	GetGameStage()->RemoveEnemy(this);
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

bool Boar::isDraw(int ex, int ey) {
	if (ex >= -1 * DRAW_CHIPNUM_X && ex <= DRAW_CHIPNUM_X) {
		if (ey >= -1 * DRAW_CHIPNUM_Y && ey <= DRAW_CHIPNUM_Y) {
			return true;
		}
	}
	return false;
}

void Boar::DefineDirection() {
	int dx = *px / CHIPSIZE - indexX;
	int dy = *py / CHIPSIZE - indexY;
	
	if (dx == 0) {
		if (dy > 0) temp = DOWN;
		else temp = UP;
	}
	else if (dy == 0) {
		if (dx > 0) temp = RIGHT;
		else temp = LEFT;
	}
	else if (dx > 0 && dy > 0) temp = DOWN_RIGHT;
	else if (dx < 0 && dy < 0) temp = UP_LEFT;
	else if (dx > 0 && dy < 0) temp = UP_RIGHT;
	else if (dx < 0 && dy > 0) temp = DOWN_LEFT;

	DrawFormatString(300, 0, GetColor(255, 0, 0), "dx:%d, dy:%d", dx, dy);
	
	dir = temp;
}

void Boar::AllWall() {
	switch (dir) {
	case UP: temp = UpCase(); break;
	case DOWN: temp = DownCase(); break;
	case RIGHT: temp = RightCase(); break;
	case LEFT: temp = LeftCase(); break;
	case UP_RIGHT: temp = Up_Right_Case(); break;
	case UP_LEFT: temp = Up_Left_Case(); break;
	case DOWN_RIGHT: temp = Down_Right_Case(); break;
	case DOWN_LEFT: temp = Down_Left_Case(); break;
	}

	dir = temp;
}

bool Boar::UpWall() {
	if (mapdata[indexY - 1][indexX].mapData == 1) return true;
	return false;
}

bool Boar::DownWall() {
	if (mapdata[indexY + 1][indexX].mapData == 1) return true;
	return false;
}

bool Boar::RightWall() {
	if (mapdata[indexY][indexX + 1].mapData == 1) return true;
	return false;
}

bool Boar::LeftWall() {
	if (mapdata[indexY][indexX - 1].mapData == 1) return true;
	return false;
}

bool Boar::Up_Right_Wall() {
	if (mapdata[indexY - 1][indexX + 1].mapData == 1) return true;
	return false;
}

bool Boar::Up_Left_Wall() {
	if (mapdata[indexY - 1][indexX - 1].mapData == 1) return true;
	return false;
}

bool Boar::Down_Right_Wall() {
	if (mapdata[indexY + 1][indexX + 1].mapData == 1) return true;
	return false;
}

bool Boar::Down_Left_Wall() {
	if (mapdata[indexY + 1][indexX - 1].mapData == 1) return true;
	return false;
}

Direction Boar::UpCase() {
	Direction temp = NONE;
	if (!UpWall()) temp = UP;
	else if (!Up_Left_Wall()) temp = UP_LEFT;
	else if (!Up_Right_Wall()) temp = UP_RIGHT;
	else if (!LeftWall()) temp = LEFT;
	else if (!RightWall()) temp = RIGHT;
	else if (!Down_Left_Wall()) temp = DOWN_LEFT;
	else if (!Down_Right_Wall()) temp = DOWN_RIGHT;
	else if (!DownWall()) temp = DOWN;

	return temp;
}

Direction Boar::DownCase() {
	Direction temp = NONE;
	if (!DownWall()) temp = DOWN;
	else if (!Down_Right_Wall()) temp = DOWN_RIGHT;
	else if (!Down_Left_Wall()) temp = DOWN_LEFT;
	else if (!RightWall()) temp = RIGHT;
	else if (!LeftWall()) temp = LEFT;
	else if (!Up_Right_Wall()) temp = UP_RIGHT;
	else if (!Up_Left_Wall()) temp = UP_LEFT;
	else if (!UpWall()) temp = UP;

	return temp;
}

Direction Boar::RightCase() {
	Direction temp = NONE;
	if (!RightWall()) temp = RIGHT;
	else if (!Up_Right_Wall()) temp = UP_RIGHT;
	else if (!Down_Right_Wall()) temp = DOWN_RIGHT;
	else if (!UpWall()) temp = UP;
	else if (!DownWall()) temp = DOWN;
	else if (!Up_Left_Wall()) temp = UP_LEFT;
	else if (!Down_Left_Wall()) temp = DOWN_LEFT;
	else if (!LeftWall()) temp = LEFT;

	return temp;
}

Direction Boar::LeftCase() {
	Direction temp = NONE;
	if (!LeftWall()) temp = LEFT;
	else if (!Down_Left_Wall()) temp = DOWN_LEFT;
	else if (!Up_Left_Wall()) temp = UP_LEFT;
	else if (!DownWall()) temp = DOWN;
	else if (!UpWall()) temp = UP;
	else if (!Down_Right_Wall()) temp = DOWN_RIGHT;
	else if (!Up_Right_Wall()) temp = UP_RIGHT;
	else if (!RightWall()) temp = RIGHT;

	return temp;
}

Direction Boar::Up_Right_Case() {
	Direction temp = NONE;
	if (!Up_Right_Wall()) temp = UP_RIGHT;
	else if (!UpWall()) temp = UP;
	else if (!RightWall()) temp = RIGHT;
	else if (!Up_Left_Wall()) temp = UP_LEFT;
	else if (!Down_Right_Wall()) temp = DOWN_RIGHT;
	else if (!LeftWall()) temp = LEFT;
	else if (!DownWall()) temp = DOWN;
	else if (!Down_Left_Wall()) temp = DOWN_LEFT;

	return temp;
}

Direction Boar::Up_Left_Case() {
	Direction temp = NONE;
	if (!Up_Left_Wall()) temp = UP_LEFT;
	else if (!LeftWall()) temp = LEFT;
	else if (!UpWall()) temp = UP;
	else if (!Down_Left_Wall()) temp = DOWN_LEFT;
	else if (!Up_Right_Wall()) temp = UP_RIGHT;
	else if (!DownWall()) temp = DOWN;
	else if (!RightWall()) temp = RIGHT;
	else if (!Down_Right_Wall()) temp = DOWN_RIGHT;

	return temp;
}

Direction Boar::Down_Right_Case() {
	Direction temp = NONE;
	if (!Down_Right_Wall()) temp = DOWN_RIGHT;
	else if (!RightWall()) temp = RIGHT;
	else if (!DownWall()) temp = DOWN;
	else if (!Up_Right_Wall()) temp = UP_RIGHT;
	else if (!Down_Left_Wall()) temp = DOWN_LEFT;
	else if (!UpWall()) temp = UP;
	else if (!LeftWall()) temp = LEFT;
	else if (!Up_Left_Wall()) temp = UP_LEFT;

	return temp;
}

Direction Boar::Down_Left_Case() {
	Direction temp = NONE;
	if (!Down_Left_Wall()) temp = DOWN_LEFT;
	else if (!DownWall()) temp = DOWN;
	else if (!LeftWall()) temp = LEFT;
	else if (!Down_Right_Wall()) temp = DOWN_RIGHT;
	else if (!Up_Left_Wall()) temp = UP_LEFT;
	else if (!RightWall()) temp = RIGHT;
	else if (!UpWall()) temp = UP;
	else if (!Up_Right_Wall()) temp = UP_RIGHT;

	return temp;
}

int Boar::gh[24];