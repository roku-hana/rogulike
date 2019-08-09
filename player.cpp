#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"spritecomponent.h"

Player::Player(GameStage* game) :Actor(game){
	if (-1 == LoadDivGraph("Images\\cat.png", 12, 3, 4, 32, 32, gh)) MSG("�v���C���[�摜�ǂݍ��݃G���[");
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetImage(gh);
	//��ňʒu��ύX
	scrollx = 96;
	scrolly = 96;
	SetPosition(Vector2(320, 256));
}

Player::~Player() {

}

void Player::updateActor() {

}

void Player::ActorInput(InputManager* input) {
	if (input->isPushRight() && scrollx < MAX_SCROLLX) scrollx += 32;
	if (input->isPushLeft() && scrollx > MIN_SCROLL) scrollx -= 32;
	if (input->isPushUp() && scrolly > MIN_SCROLL) scrolly -= 32;
	if (input->isPushDown() && scrolly < MAX_SCROLLy) scrolly += 32;
}