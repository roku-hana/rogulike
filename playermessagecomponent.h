#ifndef __PLAYERMESSAGECOMPONENT_H__
#define __PLAYERMESSAGECOMPONENT_H__

#include"component.h"
#include<vector>

using namespace std;

class Player;
class Enemy;

class PlayerMessageComponent : public Component
{
public:
	PlayerMessageComponent(class Actor* owner, int updateOrder = 10);
	void update() override;
private:
	Player* player;
	vector<Enemy*>* enemies;
	void Message();

};

#endif