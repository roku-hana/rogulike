#ifndef __BOAR_H__
#define __BOAR_H__

#include"enemy.h"
#include<vector>

using namespace std;

class RogueLikeMap;

class Boar : public Enemy {
public:
	Boar(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int *px, int* py, EnemyParameter ep);
	~Boar();
	void updateActor() override;
	void ActorInput(InputManager*) override;
private:
	static int gh[24];
	const int CHIPSIZE = 32;
};

#endif
