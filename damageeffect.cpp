#include"damageeffect.h"

DamageEffect::DamageEffect(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder) {
	anim = new AnimDraw();
}

DamageEffect::~DamageEffect() { delete anim; }


void DamageEffect::Draw(int count) {
	if (mImage) {
		if (mOwner->GetDamageFlag()) anim->DrawAnimation(0, mOwner->GetPosition().x, mOwner->GetPosition().y, count);
	}
}

void DamageEffect::SetImage(int* image) {
	SpriteComponent::SetImage(image);
	for (int i = 0; i < 2; i++) anim->SetImage(0, image[i]);
	anim->SetGap(0, 25);
}