#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"spritecomponent.h"
#include"makedungeon.h"

Player::Player(GameStage* game, vector<vector<RogueLikeMap>>& map) :Actor(game), mapdata(map){
	if (-1 == LoadDivGraph("Images\\cat.png", 12, 3, 4, 32, 32, gh)) MSG("プレイヤー画像読み込みエラー");
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetImage(gh);
	
	SetPosition(Vector2(320, 224));
}

Player::~Player() {

}

void Player::updateActor() {
	
}

void Player::ActorInput(InputManager* input) {
	if ((input->isPushRight() || RightMove(input)) && !RightWall()) scrollx += CHIPSIZE;
	if ((input->isPushLeft() || LeftMove(input)) && !LeftWall()) scrollx -= CHIPSIZE;
	if ((input->isPushUp() || UpMove(input)) && !UpWall()) scrolly -= CHIPSIZE;
	if ((input->isPushDown() || DownMove(input)) && !DownWall()) scrolly += CHIPSIZE;
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

bool Player::RightMove(InputManager* input) {
	static int time = 0;
	if (input->isPushRight(0)) time++;
	else time = 0;

	if (time % 360 == 0) return true;
	return false;
}

bool Player::LeftMove(InputManager* input) {
	static int time = 0;
	if (input->isPushLeft(0)) time++;
	else time = 0;

	if (time % 360 == 0) return true;
	return false;
}

bool Player::UpMove(InputManager* input) {
	static int time = 0;
	if (input->isPushUp(0)) time++;
	else time = 0;

	if (time % 360 == 0) return true;
	return false;
}

bool Player::DownMove(InputManager* input) {
	static int time = 0;
	if (input->isPushDown(0)) time++;
	else time = 0;

	if (time % 360 == 0) return true;
	return false;
}