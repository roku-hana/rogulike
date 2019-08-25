#ifndef __DAMAGEEFFECT_H__
#define __DAMAGEEFFECT_H__

#include"spritecomponent.h"
#include"animdraw.h"
#include"actor.h"

class DamageEffect : public SpriteComponent {
public:
	DamageEffect(Actor* owner, int drawOrder);
	~DamageEffect();
	void Draw(int count) override;
	void SetImage(int* image) override;
private:
	AnimDraw* anim;
	static int damageEffect;
};

#endif