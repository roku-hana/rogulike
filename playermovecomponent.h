#ifndef __PLAYERMOVECOMPONENT_H__
#define __PLAYERMOVECOMPONENT_H__

#include"component.h"

class Player;

class PlayerMoveComponent : public Component
{
public:
	PlayerMoveComponent(class Actor* owner, int updateOrder = 10);
	void update() override;
private:
	int* px;
	int* py;
	Player* player;
	const int CHIPSIZE = 32;
};

#endif
