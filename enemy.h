#ifndef __ENEMY_H__
#define __ENEMY_H__

#include"Actor.h"
#include<vector>
#include<string>
using namespace std;

class RogueLikeMap;

struct EnemyParameter{
	int nowhp;
	int maxhp;
	int attack;
	int defense;
	int id;
	int experiense;
};

class Enemy : public Actor {
public:
	Enemy(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int* px, int* py);
	~Enemy();
	int GetIndexX() { return indexX; }
	int GetIndexY() { return indexY; }
	string GetEnemyName(int i) { return names[i]; }
	EnemyParameter GetEnemyParam() { return param; }
protected:
	const int* px;
	const int* py;
	int indexX, indexY;
	Direction temp;
	EnemyParameter param;
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
	static vector<string> names;
private:
	void LoadName();
};

#endif
