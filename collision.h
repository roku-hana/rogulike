#ifndef __COLLISION_H__
#define __COLLISION_H__

#include<vector>
using namespace std;

class GameStage;
class Player;
class Chick;

class Collision {
public:
	Collision(GameStage* gs);
	~Collision();
	void Player_Chick_Collision();
private:
	Player* player;
	vector<Chick*> chicks;
};

#endif
