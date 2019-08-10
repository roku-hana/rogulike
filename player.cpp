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
}

Player::~Player() {

}

void Player::updateActor() {
	
}

void Player::ActorInput(InputManager* input) {
	if (input->isPushRight() && !RightWall()) {
		scrollx += CHIPSIZE; 
		dir = RIGHT;
	}
	if (input->isPushLeft() && !LeftWall()) {
		scrollx -= CHIPSIZE;
		dir = LEFT;
	}
	if (input->isPushUp() && !UpWall()) {
		scrolly -= CHIPSIZE;
		dir = UP;
	}
	if (input->isPushDown() && !DownWall()) {
		scrolly += CHIPSIZE;
		dir = DOWN;
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