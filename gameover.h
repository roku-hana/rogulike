#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include"game.h"

class GameStage;

class GameOver : public GameScene {
public:
	GameOver(Game* pManager, SceneManager* sManager);
	~GameOver() {};
	void update();
	void draw();
private:
	int count;
	int BigFont;
};

#endif
