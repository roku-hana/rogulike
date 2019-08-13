#ifndef __NEXTSTAGE_H__
#define __NEXTSTAGE_H__

#include"game.h"

class NextStage : public Scene {
public:
	NextStage(SceneManager* sManager, int num);
	~NextStage();
	void update();
	void draw();
private:
	int stageNum;
	int count;
};

#endif