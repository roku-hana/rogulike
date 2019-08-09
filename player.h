#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"Actor.h"

class GameStage;
class InputManager;

class Player : public Actor{
public:
	Player(GameStage* game);
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
	//Ç±ÇÃílÇÕå„Ç≈ïœçXÇ∑ÇÈ
	const int MAX_SCROLLX = 2240;
	const int MAX_SCROLLY = 1680;
	const int MIN_SCROLLX = 320;
	const int MIN_SCROLLY = 240;
};

#endif
