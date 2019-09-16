#ifndef __PLAY_H__
#define __PLAY_H__

#include"game.h"

class GameStage;

struct Cursole {
	int pos;
	int x, y;
	int r;
};

class Play : public GameScene {
public:
	Play(Game* pManager, SceneManager* sManager);
	~Play() {};
	void update();
	void draw();
private:
	GameStage* gamestage;
	Cursole cur;
};

#endif
