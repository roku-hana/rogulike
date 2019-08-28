#ifndef __PLAY_H__
#define __PLAY_H__

#include"game.h"

class GameStage;

class Play : public GameScene {
public:
	Play(Game* pManager, SceneManager* sManager);
	~Play() {};
	void update();
	void draw();
private:
	GameStage* gamestage;
};

#endif
