#ifndef __CHARACTERSPRITE_H__
#define __CHARACTERSPRITE_H__

#include"spritecomponent.h"
#include"animdraw.h"
#include"actor.h"

class CharacterSprite : public SpriteComponent {
public:
	CharacterSprite(Actor* owner, int drawOrder);
	~CharacterSprite();
	void Draw(int count, Direction dir) override;
	void SetImage(int* image) override;
private:
	AnimDraw* anim;
};

#endif
