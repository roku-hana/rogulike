#ifndef __SPRITECOMPONENT_H__
#define __SPRITECOMPONENT_H__

#include"component.h"

enum Direction;

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(int count);
	virtual void SetImage(int* image);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mImgHeight; }
	int GetTexWidth() const { return mImgWidth; }
protected:
	int* mImage;
	int mDrawOrder;
	int mImgWidth;
	int mImgHeight;
};


#endif