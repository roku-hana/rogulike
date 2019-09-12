#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"Actor.h"
#include<vector>
#include<string>
using namespace std;

class GameStage;
class InputManager;
class RogueLikeMap;
class Enemy;

struct PlayerParameter {
	int nowhp;
	int maxhp;
	int attack;
	int defense;
	int level;
	int experience;
	string name;
};

// アイテムに関するフラグ
//const unsigned int BIT_FLAG_0 = (1 << 0); // 0000 0000 0000 0001
//const unsigned int BIT_FLAG_1 = (1 << 1); // 0000 0000 0000 0010
//const unsigned int BIT_FLAG_2 = (1 << 2); // 0000 0000 0000 0100
//const unsigned int BIT_FLAG_3 = (1 << 3); // 0000 0000 0000 1000
//const unsigned int BIT_FLAG_4 = (1 << 4); // 0000 0000 0001 0000
//const unsigned int BIT_FLAG_5 = (1 << 5); // 0000 0000 0010 0000
//const unsigned int BIT_FLAG_6 = (1 << 6); // 0000 0000 0100 0000
//const unsigned int BIT_FLAG_7 = (1 << 7); // 0000 0000 1000 0000

class Player : public Actor{
public:
	Player(GameStage* game, vector<vector<RogueLikeMap>>& map);
	~Player();

	void updateActor() override;
	void ActorInput(InputManager*) override;
	int* GetScrollX() { return &scrollx; }
	int* GetScrollY() { return &scrolly; }
	void SetScrollX(int sx) { scrollx = sx; }
	void SetScrollY(int sy) { scrolly = sy; }
	void AddChickNum() { chickNum++; }
	int GetChickNum() { return chickNum; }
	bool RightWall();
	bool LeftWall();
	bool UpWall();
	bool DownWall();
	bool Up_Right_Wall();
	bool Up_Left_Wall();
	bool Down_Right_Wall();
	bool Down_Left_Wall();
	void SetActState(ActState as) { this->as = as; }
	ActState GetActState() { return as; }
	PlayerParameter GetPlayerParam() { return param; }
	void SetPlayerParam(PlayerParameter& param);
	void SetExperience(int exp) { param.experience = exp; }
	void SetDirBox(int knd) { *dirbox = knd; }
	int GetDirBox() { return *dirbox; }
	void SetEnemyAddFlag(bool flag) { enemyaddflag = flag; }
	bool GetEnemyAddFlag() { return enemyaddflag; }
	///////////////////////
	void SetItemFlag(int flag) { itemflag = flag; }
	int GetItemFlag() { return itemflag; }
	//////////////////////
private:
	int scrollx, scrolly;
	int gh[24];
	static int chickNum;
	const vector<vector<RogueLikeMap>> mapdata;
	ActState as;
	PlayerParameter param;
	static int damageeffect[2];
	int* dirbox;
	int actcount;
	bool enemyaddflag;
	//////////////
	int itemflag;
	//////////////
};

#endif
