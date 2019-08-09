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
private:
	int scrollx, scrolly;
	int gh[12];
	//Ç±ÇÃílÇÕå„Ç≈ïœçXÇ∑ÇÈ
	const int MAX_SCROLLX = 1280;
	const int MAX_SCROLLy = 512;
	const int MIN_SCROLL = 96;
};

#endif
