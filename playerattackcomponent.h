#ifndef __PLAYERATTACKCOMPONENT_H__
#define __PLAYERATTACKCOMPONENT_H__

#include"component.h"
#include<vector>

using namespace std;

class Player;
class Enemy;

class PlayerAttackComponent : public Component
{
public:
	PlayerAttackComponent(class Actor* owner, int updateOrder = 10);
	void update() override;
private:
	Player* player;
	vector<Enemy*>* enemies;
	void Attack();
	void Message();
	int timerstart;
	int enemyKnd;
	static int messagebox;
};

#endif
