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
	
	SetPosition(Vector2(320, 256));
}

Player::~Player() {

}

void Player::updateActor() {
	
}

void Player::ActorInput(InputManager* input) {
	if (input->isPushRight() && !RightWall()) scrollx += 32;
	if (input->isPushLeft() && !LeftWall()) scrollx -= 32;
	if (input->isPushUp() && !UpWall()) scrolly -= 32;
	if (input->isPushDown() && !DownWall()) scrolly += 32;
}

bool Player::RightWall() {
	int px = scrollx / 32;
	int py = scrolly / 32;
	if (mapdata[py][px + 1].mapData == 1) return true;
	return false;
}

bool Player::LeftWall() {
	int px = scrollx / 32;
	int py = scrolly / 32;
	if (mapdata[py][px - 1].mapData == 1) return true;
	return false;
}

bool Player::UpWall() {
	int px = scrollx / 32;
	int py = scrolly / 32;
	if (mapdata[py - 1][px].mapData == 1) return true;
	return false;
}

bool Player::DownWall() {
	int px = scrollx / 32;
	int py = scrolly / 32;
	if (mapdata[py + 1][px].mapData == 1) return true;
	return false;
}