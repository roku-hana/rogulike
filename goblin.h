#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include"enemy.h"
#include<vector>

using namespace std;

class RogueLikeMap;

class Goblin : public Enemy {
public:
	Goblin(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int* px, int* py, EnemyParameter ep);
	~Goblin();
	void updateActor() override;
	void ActorInput(InputManager*) override;
private:
	static int gh[24];
	const int CHIPSIZE = 32;
};

#endif
