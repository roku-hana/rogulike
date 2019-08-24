#include"enemy.h"
#include"gamestage.h"
#include"makedungeon.h"
#include"charactersprite.h"
#include<fstream>
#include"gamestage.h"
#include"player.h"

//
//#include<DxLib.h>
//

const int DRAW_PLAYER_X = 320;
const int DRAW_PLAYER_Y = 224;

Enemy::Enemy(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int* px, int* py)
	:Actor(game), mapdata(map),
	px(px), py(py), indexX(x), indexY(y)
{
	game->AddEnemy(this);

	//名前一覧取得
	if (names.empty()) LoadName();
}

Enemy::~Enemy() {
	GetGameStage()->RemoveEnemy(this);
}

void Enemy::updateActor() {
	int ex = indexX - *px / CHIPSIZE;
	int ey = indexY - *py / CHIPSIZE;
	Vector2 setpos = { DRAW_PLAYER_X + ex * CHIPSIZE, DRAW_PLAYER_Y + ey * CHIPSIZE };
	if (isDraw(ex, ey)) {
		if (moveflag) SetPosition(setpos);
	}
	else SetPosition(Vector2(-100, -100));

	moveflag = GetGameStage()->GetPlayer()->GetMoveFlag();

	if (moveflag) {
		DefineDirection();
		AllWall();
	}

	if (as == WAIT) {
		move_act();
	}
}

bool Enemy::isDraw(int ex, int ey) {
	if(GetGameStage()->GetMapData()->GetLightKnd() == 1){
		if (ex >= -1 * DRAW_CHIPNUM_X && ex <= DRAW_CHIPNUM_X) {
			if (ey >= -1 * DRAW_CHIPNUM_Y && ey <= DRAW_CHIPNUM_Y) {
				return true;
			}
		}
	}
	if (GetGameStage()->GetMapData()->GetLightKnd() == 2) {
		if (ex >= -1 && ex <= 1) {
			if (ey >= -1 && ey <= 1) {
				return true;
			}
		}
	}
	return false;
}

void Enemy::DefineDirection() {
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

	dir = temp;
}

void Enemy::AllWall() {
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

bool Enemy::UpWall() {
	if (mapdata[indexY - 1][indexX].mapData == 1) return true;
	return false;
}

bool Enemy::DownWall() {
	if (mapdata[indexY + 1][indexX].mapData == 1) return true;
	return false;
}

bool Enemy::RightWall() {
	if (mapdata[indexY][indexX + 1].mapData == 1) return true;
	return false;
}

bool Enemy::LeftWall() {
	if (mapdata[indexY][indexX - 1].mapData == 1) return true;
	return false;
}

bool Enemy::Up_Right_Wall() {
	if (mapdata[indexY - 1][indexX + 1].mapData == 1) return true;
	return false;
}

bool Enemy::Up_Left_Wall() {
	if (mapdata[indexY - 1][indexX - 1].mapData == 1) return true;
	return false;
}

bool Enemy::Down_Right_Wall() {
	if (mapdata[indexY + 1][indexX + 1].mapData == 1) return true;
	return false;
}

bool Enemy::Down_Left_Wall() {
	if (mapdata[indexY + 1][indexX - 1].mapData == 1) return true;
	return false;
}

Direction Enemy::UpCase() {
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

Direction Enemy::DownCase() {
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

Direction Enemy::RightCase() {
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

Direction Enemy::LeftCase() {
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

Direction Enemy::Up_Right_Case() {
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

Direction Enemy::Up_Left_Case() {
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

Direction Enemy::Down_Right_Case() {
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

Direction Enemy::Down_Left_Case() {
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

void Enemy::LoadName() {
	std::string temp;
	ifstream fp("enemydata\\enemyname.txt");
	if (fp.fail()) MSG("ファイル読み込みエラー");
	while (std::getline(fp, temp)) names.push_back(temp);
}

void Enemy::move_act() {
	int dx = abs(indexX - *px / CHIPSIZE);
	int dy = abs(indexY - *py / CHIPSIZE);

	if ((dx == 1 || dy == 1) && dx + dy <= 2) as = ACT_BEGIN;
	else as = MOVE_BEGIN;
}

vector<string> Enemy::names;