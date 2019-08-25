#ifndef __ENEMYATTACKCOMPONENT_H__
#define __ENEMYATTACKCOMPONENT_H__

#include"component.h"
#include<vector>

using namespace std;

class Player;
class Enemy;

class EnemyAttackComponent : public Component
{
public:
	EnemyAttackComponent(class Actor* owner, int* x, int* y, int updateOrder = 10);
	void update() override;
private:
	Player* player;
	Enemy* enemy;
	void Attack();
	void Message();
	void Animation();
	int timerstart;
	bool messageflag;
	int* ex;
	int* ey;
	int count;
};

#endif
