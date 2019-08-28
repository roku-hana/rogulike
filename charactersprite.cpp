#include"charactersprite.h"

CharacterSprite::CharacterSprite(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder) { 
	anim = new AnimDraw(); 
	damagecount = 0;
}

CharacterSprite::~CharacterSprite() { delete anim; }

void CharacterSprite::Draw(int count) {
	if (mOwner->GetDamageFlag()) {
		damagecount = 50;
		mOwner->SetDamageFlag(false);
	}
	else {
		if (damagecount > 0) damagecount--;
	}
	if (mImage) {
		Vector2 pos = mOwner->GetPosition();
		int posx = (int)pos.x;
		int posy = (int)pos.y;
		if (damagecount % 5 == 0) {
			switch (mOwner->GetDirection()) {
			case DOWN: anim->DrawAnimation(0, posx, posy, count); break;
			case LEFT: anim->DrawAnimation(2, posx, posy, count); break;
			case UP_LEFT: anim->DrawAnimation(5, posx, posy, count); break;
			case DOWN_LEFT: anim->DrawAnimation(1, posx, posy, count); break;
			case RIGHT: anim->DrawAnimation(4, posx, posy, count); break;
			case UP_RIGHT: anim->DrawAnimation(7, posx, posy, count); break;
			case DOWN_RIGHT: anim->DrawAnimation(3, posx, posy, count); break;
			case UP: anim->DrawAnimation(6, posx, posy, count); break;
			default: break;
			}
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