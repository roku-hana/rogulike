#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"charactersprite.h"
#include"makedungeon.h"


Player::Player(GameStage* game, vector<vector<RogueLikeMap>>& map) :Actor(game), mapdata(map){
	if (-1 == LoadDivGraph("Images\\Chicken_black.png", 24, 6, 4, 32, 32, gh)) MSG("プレイヤー画像読み込みエラー");
	SpriteComponent* sc = new CharacterSprite(this, 100);
	sc->SetImage(gh);
	
	SetPosition(Vector2(320, 224));
	dir = DOWN;
	count = 0; 
	ismoving = false;
	scrollx = 0;
	scrolly = 0;
}

Player::~Player() {

}

void Player::updateActor() {
	Move();
}

void Player::ActorInput(InputManager* input) {
	if (input->isPushRight(0)) {
		if (input->isPushUp(0))dir = UP_RIGHT;
		else if (input->isPushDown(0)) dir = DOWN_RIGHT;
		else dir = RIGHT;
		if (count == 0) count = GetNowCount();
		ismoving = true;
	}
	else if (input->isPushLeft(0)) {
		if (input->isPushUp(0)) dir = UP_LEFT;
		else if (input->isPushDown(0)) dir = DOWN_LEFT;
		else dir = LEFT;
		if (count == 0) count = GetNowCount();
		ismoving = true;
	}
	else if (input->isPushUp(0)) {
		if (input->isPushRight(0)) dir = UP_RIGHT;
		else if (input->isPushLeft(0)) dir = UP_LEFT;
		else dir = UP;
		if (count == 0) count = GetNowCount();
		ismoving = true;
	}
	else if (input->isPushDown(0)) {
		if (input->isPushRight(0)) dir = DOWN_RIGHT;
		else if (input->isPushLeft(0)) dir = DOWN_LEFT;
		else dir = DOWN;
		if (count == 0) count = GetNowCount();
		ismoving = true;
	}
	else {
		count = 0;
		ismoving = false;
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

void Player::Move() {
	if (ismoving) {
		if (CanMove()) {
			switch (dir) {
			case UP: if (!UpWall()) scrolly -= CHIPSIZE; break;
			case DOWN: if (!DownWall()) scrolly += CHIPSIZE; break;
			case RIGHT: if (!RightWall()) scrollx += CHIPSIZE; break;
			case LEFT: if (!LeftWall()) scrollx -= CHIPSIZE; break;
			case UP_RIGHT: if (!Up_Right_Wall()) { scrollx += CHIPSIZE; scrolly -= CHIPSIZE; } break;
			case UP_LEFT: if (!Up_Left_Wall()) { scrollx -= CHIPSIZE; scrolly -= CHIPSIZE; } break;
			case DOWN_RIGHT: if (!Down_Right_Wall()) { scrollx += CHIPSIZE; scrolly += CHIPSIZE; } break;
			case DOWN_LEFT: if (!Down_Left_Wall()) {scrollx -= CHIPSIZE; scrolly += CHIPSIZE; } break;
			default: break;
			}
		}
	}
}

bool Player::CanMove() {
	if (GetNowCount() - count <= 30 || GetNowCount() - count >= 300) return true;
	return false;
}