#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"playersprite.h"
#include"makedungeon.h"
#include"animdraw.h"

//tewicontrolファイルを見て、長押し移動を実装する

Player::Player(GameStage* game, vector<vector<RogueLikeMap>>& map) :Actor(game), mapdata(map){
	if (-1 == LoadDivGraph("Images\\cat.png", 12, 3, 4, 32, 32, gh)) MSG("プレイヤー画像読み込みエラー");
	SpriteComponent* sc = new PlayerSprite(this, 150);
	sc->SetImage(gh);
	
	SetPosition(Vector2(320, 224));
	dir = DOWN;
	count = 0; 
	ismoving = false;
}

Player::~Player() {

}

void Player::updateActor() {
	Move();
}

void Player::ActorInput(InputManager* input) {
	if (input->isPushRight(0)) {
		dir = RIGHT;
		if (count == 0) count = GetNowCount();
		ismoving = true;
	}
	else if (input->isPushLeft(0)) {
		dir = LEFT;
		if (count == 0) count = GetNowCount();
		ismoving = true;
	}
	else if (input->isPushUp(0)) {
		dir = UP;
		if (count == 0) count = GetNowCount();
		ismoving = true;
	}
	else if (input->isPushDown(0)) {
		dir = DOWN;
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

void Player::Move() {
	if (ismoving) {
		if (CanMove()) {
			switch (dir) {
			case UP: if (!UpWall()) scrolly -= CHIPSIZE; break;
			case DOWN: if (!DownWall()) scrolly += CHIPSIZE; break;
			case RIGHT: if (!RightWall()) scrollx += CHIPSIZE; break;
			case LEFT: if (!LeftWall()) scrollx -= CHIPSIZE; break;
			default: break;
			}
		}
	}
}

bool Player::CanMove() {
	if (GetNowCount() - count <= 30 || GetNowCount() - count >= 300) return true;
	return false;
}