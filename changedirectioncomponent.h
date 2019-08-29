#ifndef __CHANGEDIRECTIONCOMPONENT_H__
#define __CHANGEDIRECTIONCOMPONENT_H__

#include"component.h"

class InputManager;
class Player;

class ChangeDirectionComponent : public Component
{
public:
	ChangeDirectionComponent(class Actor* owner, int updateOrder = 10);
	void update() override;
	void ProcessInput(InputManager*) override;
private:
	Player* player;
	const int CHIPSIZE = 32;
};

#endif
