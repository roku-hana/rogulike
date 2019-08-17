#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"Actor.h"
#include<vector>
using namespace std;

class GameStage;
class InputManager;
class RogueLikeMap;

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
	bool CanMove();
	bool RightWall();
	bool LeftWall();
	bool UpWall();
	bool DownWall();
	bool Up_Right_Wall();
	bool Up_Left_Wall();
	bool Down_Right_Wall();
	bool Down_Left_Wall();
private:
	int scrollx, scrolly;
	int gh[24];
	int count;
	static int chickNum;
	const vector<vector<RogueLikeMap>> mapdata;
	void Move();
};

#endif
