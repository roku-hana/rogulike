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
	void updateActor() override;
	int GetIndexX() const { return indexX; }
	int GetIndexY() const { return indexY; }
	string GetEnemyName(int i) { return names[i]; }
	void SetActState(ActState as) { this->as = as; }
	ActState GetActState() { return as; }
	EnemyParameter GetEnemyParam() { return param; }
	void SetWaitTime(int time) { waittime = time; }
	int GetWaitTime() { return waittime; }
	int GetEpx() const { return epx; }
	int GetEpy() const { return epy; }
	//void SetAddX(int x) { addx = x; }
	//void SetAddY(int y) { addy = y; }
	//int GetAddX() { return addx; }
	//int GetAddY() { return addy; }
	//int GetCount() { return count; }
	void DefineDirection();
protected:
	const int* px;
	const int* py;
	int indexX, indexY;
	Direction temp;
	EnemyParameter param;
	bool isDraw(int cx, int cy);
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
	ActState as;
private:
	void LoadName();
	void move_act();
	static int damageeffect[2];
	static vector<Enemy*> mEnemies;
	int waittime;
	int timerstart;
	int epx, epy;
	//int count;
	//int addx, addy;
	//bool animflag;
};

#endif
