#ifndef __PAUSE_H__
#define __PAUSE_H__

#include"game.h"

class Pause : public GameScene {
public:
	Pause(Game* pManager, SceneManager* sManager);
	~Pause() {};
	void update();
	void draw();
private:
	int back;
};

#endif
