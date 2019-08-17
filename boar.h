#ifndef __BOAR_H__
#define __BOAR_H__

#include"Actor.h"
#include<vector>

using namespace std;

class RogueLikeMap;

class Boar : public Actor {
public:
	Boar(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int* px, int* py);
	~Boar();
	void updateActor() override;
	void ActorInput(InputManager*) override;
	int GetIndexX() { return indexX; }
	int GetIndexY() { return indexY; }
private:
	static int gh[24];
	const int* px;
	const int* py;
	int indexX, indexY;
	Direction temp;
	bool isDraw(int cx, int cy);
	void DefineDirection();
	bool RightWall();
	bool LeftWall();
	bool UpWall();
	bool DownWall();
	bool Up_Right_Wall();
	bool Up_Left_Wall();
	bool Down_Right_Wall();
	bool Down_Left_Wall();
	Direction UpCase();
	Direction DownCase();
	Direction RightCase();
	Direction LeftCase();
	Direction Up_Right_Case();
	Direction Up_Left_Case();
	Direction Down_Right_Case();
	Direction Down_Left_Case();
	void AllWall();
	const vector<vector<RogueLikeMap>> mapdata;
};

#endif
