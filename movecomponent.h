#ifndef __MOVECOMPONENT_H__
#define __MOVECOMPONENT_H__

#include"component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void update() override;
private:
	int moveX, moveY;
	const int AMOUNT_OF_MOVEMENT = 32;
};


#endif