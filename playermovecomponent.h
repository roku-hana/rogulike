#ifndef __PLAYERMOVECOMPONENT_H__
#define __PLAYERMOVECOMPONENT_H__

#include"component.h"
#include<vector>

class Player;
class Enemy;

class PlayerMoveComponent : public Component
{
public:
	PlayerMoveComponent(class Actor* owner, int updateOrder = 10);
	void update() override;
private:
	int* px;
	int* py;
	Player* player;
	std::vector<Enemy*>* enemies;
	const int CHIPSIZE = 32;
	void Move();
};

#endif
