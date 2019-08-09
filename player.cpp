#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"spritecomponent.h"

Player::Player(GameStage* game) :Actor(game){
	if (-1 == LoadDivGraph("Images\\cat.png", 12, 3, 4, 32, 32, gh)) MSG("�v���C���[�摜�ǂݍ��݃G���[");
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetImage(gh);
	
	SetPosition(Vector2(320, 256));
}

Player::~Player() {

}

void Player::updateActor() {
	
}

void Player::ActorInput(InputManager* input) {
	//��ŕǂł������Ȃ��悤�ɕύX����
	if (input->isPushRight() && scrollx < MAX_SCROLLX) scrollx += 40;
	if (input->isPushLeft() && scrollx > MIN_SCROLLX) scrollx -= 40;
	if (input->isPushUp() && scrolly > MIN_SCROLLY) scrolly -= 40;
	if (input->isPushDown() && scrolly < MAX_SCROLLY) scrolly += 40;
}