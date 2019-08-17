#ifndef __ENEMYMOVECOMPONENT_H__
#define __ENEMYMOVECOMPONENT_H__

#include"component.h"

class EnemyMoveComponent : public Component
{
public:
	EnemyMoveComponent(class Actor* owner, int* ex, int* ey, int updateOrder = 10);
	void update() override;
private:
	int* ex;
	int* ey;
};

#endif
