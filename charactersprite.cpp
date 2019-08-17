#include"charactersprite.h"

CharacterSprite::CharacterSprite(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder) { anim = new AnimDraw(); }

CharacterSprite::~CharacterSprite() { delete anim; }

void CharacterSprite::Draw(int count) {
	if (mImage) {
		Vector2 pos = mOwner->GetPosition();
		switch (mOwner->GetDirection()) {
		case DOWN: anim->DrawAnimation(0, pos.x, pos.y, count); break;
		case LEFT: anim->DrawAnimation(2, pos.x, pos.y, count); break;
		case UP_LEFT: anim->DrawAnimation(5, pos.x, pos.y, count); break;
		case DOWN_LEFT: anim->DrawAnimation(1, pos.x, pos.y, count); break;
		case RIGHT: anim->DrawAnimation(4, pos.x, pos.y, count); break;
		case UP_RIGHT: anim->DrawAnimation(7, pos.x, pos.y, count); break;
		case DOWN_RIGHT: anim->DrawAnimation(3, pos.x, pos.y, count); break;
		case UP: anim->DrawAnimation(6, pos.x, pos.y, count); break;
		default: break;
		}
	}
}

void CharacterSprite::SetImage(int* image) {
	SpriteComponent::SetImage(image);
	int apid;
	for (int i = 0; i < 24; i++) {
		apid = i / 3;
		anim->SetImage(apid, image[i]);
		anim->SetGap(apid, 15);
	}
}