#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"charactersprite.h"
#include"makedungeon.h"
#include"playermovecomponent.h"
#include"playerattackcomponent.h"
//#include"playermessagecomponent.h"

Player::Player(GameStage* game, vector<vector<RogueLikeMap>>& map) :Actor(game), mapdata(map){
	if (-1 == LoadDivGraph("Images\\Chicken_black.png", 24, 6, 4, 32, 32, gh)) MSG("プレイヤー画像読み込みエラー");
	SpriteComponent* sc = new CharacterSprite(this, 100);
	sc->SetImage(gh);

	PlayerMoveComponent* pmc = new PlayerMoveComponent(this);
	PlayerAttackComponent* pac = new PlayerAttackComponent(this);
	//PlayerMessageComponent* psc = new PlayerMessageComponent(this);

	SetPosition(Vector2(320, 224));
	dir = DOWN;
	count = 0; 
	moveflag = false;
	scrollx = 0;
	scrolly = 0;
	chickNum = 0;
	as = KEY_INPUT;
	//parameterの初期化
	param.attack = 10;
	param.defense = 10;
	param.experience = 0;
	param.level = 1;
	param.maxhp = 10;
	param.nowhp = 10;
	//仮
	param.name = "にわとり";
}

Player::~Player() {

}

void Player::updateActor() {
	if (as == ACT_END || as == MOVE_END) as = KEY_INPUT;
}

void Player::ActorInput(InputManager* input) {
	if (as == KEY_INPUT) {
		if (input->isPushRight(0)) {
			if (input->isPushUp(0))dir = UP_RIGHT;
			else if (input->isPushDown(0)) dir = DOWN_RIGHT;
			else dir = RIGHT;
			if (count == 0) count = GetNowCount();
			moveflag = true;
			as = MOVE_BEGIN;
		}
		else if (input->isPushLeft(0)) {
			if (input->isPushUp(0)) dir = UP_LEFT;
			else if (input->isPushDown(0)) dir = DOWN_LEFT;
			else dir = LEFT;
			if (count == 0) count = GetNowCount();
			moveflag = true;
			as = MOVE_BEGIN;
		}
		else if (input->isPushUp(0)) {
			if (input->isPushRight(0)) dir = UP_RIGHT;
			else if (input->isPushLeft(0)) dir = UP_LEFT;
			else dir = UP;
			if (count == 0) count = GetNowCount();
			moveflag = true;
			as = MOVE_BEGIN;
		}
		else if (input->isPushDown(0)) {
			if (input->isPushRight(0)) dir = DOWN_RIGHT;
			else if (input->isPushLeft(0)) dir = DOWN_LEFT;
			else dir = DOWN;
			if (count == 0) count = GetNowCount();
			moveflag = true;
			as = MOVE_BEGIN;
		}
		else {
			count = 0;
			moveflag = false;
		}
		if (input->isPushB(0)) as = ACT_BEGIN;
	}
}

bool Player::RightWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py][px + 1].mapData == 1) return true;
	return false;
}

bool Player::LeftWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py][px - 1].mapData == 1) return true;
	return false;
}

bool Player::UpWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py - 1][px].mapData == 1) return true;
	return false;
}

bool Player::DownWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py + 1][px].mapData == 1) return true;
	return false;
}

bool Player::Up_Right_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py - 1][px + 1].mapData == 1) return true;
	return false;
}

bool Player::Up_Left_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py - 1][px - 1].mapData == 1) return true;
	return false;
}

bool Player::Down_Right_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py + 1][px + 1].mapData == 1) return true;
	return false;
}

bool Player::Down_Left_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	if (mapdata[py + 1][px - 1].mapData == 1) return true;
	return false;
}

bool Player::CanMove() {
	if (GetNowCount() - count <= 30 || GetNowCount() - count >= 300) return true;
	return false;
}

int Player::chickNum;