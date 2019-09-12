#ifndef __COLLISION_H__
#define __COLLISION_H__

#include<vector>
using namespace std;

class GameStage;

class Collision {
public:
	Collision(GameStage* gs);
	~Collision();
	void Player_Chick_Collision();
	void Player_Item_Collision();
private:
	GameStage* gs;
};

#endif
