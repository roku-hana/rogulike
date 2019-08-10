#ifndef __PLAYERSPRITE_H__
#define __PLAYERSPRITE_H__

#include"spritecomponent.h"
#include"animdraw.h"
#include"actor.h"

class PlayerSprite : public SpriteComponent {
public:
	PlayerSprite(Actor* owner, int drawOrder);
	~PlayerSprite();
	void Draw(int count, Direction dir) override;
	void SetImage(int* image) override;
private:
	AnimDraw* anim;
};

PlayerSprite::PlayerSprite(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder) { anim = new AnimDraw(); }

PlayerSprite::~PlayerSprite() { delete anim; }

void PlayerSprite::Draw(int count, Direction dir) {
	if (mImage) {
		Vector2 pos = mOwner->GetPosition();
		switch (dir) {
		case DOWN: anim->DrawAnimation(0, pos.x, pos.y, count); break;
		case LEFT:
		case UP_LEFT:
		case DOWN_LEFT:
			anim->DrawAnimation(1, pos.x, pos.y, count); break;
		case RIGHT:
		case UP_RIGHT:
		case DOWN_RIGHT:
			anim->DrawAnimation(2, pos.x, pos.y, count); break;
		case UP: anim->DrawAnimation(3, pos.x, pos.y, count); break;
		}
	}
}

void PlayerSprite::SetImage(int* image) {
	SpriteComponent::SetImage(image);
	//下向きアニメーション
	for (int i = 0; i < 3; i++) {
		anim->SetImage(0, image[i]);
		anim->SetGap(0, 15);
	}
	//左向きアニメーション
	for (int i = 3; i < 6; i++) {
		anim->SetImage(1, image[i]);
		anim->SetGap(1, 15);
	}
	//右向きアニメーション
	for (int i = 6; i < 9; i++) {
		anim->SetImage(2, image[i]);
		anim->SetGap(2, 15);
	}
	//上向きアニメーション
	for (int i = 9; i < 12; i++) {
		anim->SetImage(3, image[i]);
		anim->SetGap(3, 15);
	}
}

#endif
