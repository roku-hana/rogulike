#ifndef __CHICK_H__
#define __CHICK_H__

#include"Actor.h"

class Chick : public Actor {
public:
	Chick(GameStage* game, int x, int y, int* px, int* py);
	~Chick();
	void updateActor() override;
	void ActorInput(InputManager*) override;
	int GetIndexX() { return indexX; }
	int GetIndexY() { return indexY; }
private:
	static int gh[24];
	const int* px;
	const int* py;
	int indexX, indexY;
	bool player;
	bool isDraw(int cx, int cy);
};

#endif
