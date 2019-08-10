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
	int GetScrollX() { return scrollx; }
	int GetScrollY() { return scrolly; }
	void SetScrollX(int sx) { scrollx = sx; }
	void SetScrollY(int sy) { scrolly = sy; }
private:
	int scrollx, scrolly;
	int gh[12];
	const vector<vector<RogueLikeMap>> mapdata;
	bool RightWall();
	bool LeftWall();
	bool UpWall();
	bool DownWall();
	bool RightMove(InputManager*);
	bool LeftMove(InputManager*);
	bool UpMove(InputManager*);
	bool DownMove(InputManager*);
};

#endif
