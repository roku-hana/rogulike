#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"spritecomponent.h"

Player::Player(GameStage* game) :Actor(game){
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
	//後で壁でうごけないように変更する
	if (input->isPushRight()) scrollx += 32;
	if (input->isPushLeft()) scrollx -= 32;
	if (input->isPushUp()) scrolly -= 32;
	if (input->isPushDown()) scrolly += 32;
}