#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"Actor.h"
#include<vector>
using namespace std;

class GameStage;
class InputManager;
class RogueLikeMap;
enum Direction;

class Player : public Actor{
public:
	Player(GameStage* game, vector<vector<RogueLikeMap>>& map);
	~Player();

	void updateActor() override;
	void ActorInput(InputManager*) override;
	int GetScrollX() { return scrollx; }
	int GetScrollY() { return scrolly; }
	void SetScrollX(int sx) { scrollx = sx; }
	void SetScrollY(int sy) { scrolly = sy; }
	Direction GetDir() { return dir; }
private:
	int scrollx, scrolly;
	int gh[12];
	int count;
	const vector<vector<RogueLikeMap>> mapdata;
	bool RightWall();
	bool LeftWall();
	bool UpWall();
	bool DownWall();
	void Move();
	bool CanMove();
	Direction dir;
	bool ismoving;
};

#endif
