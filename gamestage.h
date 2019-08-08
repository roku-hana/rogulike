#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include<vector>

class MapData;

class GameStage {
public:
	GameStage();
	~GameStage();
	void update();
	void draw();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
private:
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	MapData* mp;
};

#endif
