#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include<vector>
#include<string>

class MapData;
class Player;
class StageTest;
class InputManager;
class Chick;
class Collision;

class GameStage {
public:
	GameStage(InputManager* temp);
	~GameStage();
	void update();
	void draw();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void AddChick(Chick* chick);
	void RemoveChick(Chick* chick);
	void ProcessInput();
	int NextStage() { return nextStage; }
	MapData* GetMapData() { return mp; }
	Player* GetPlayer() { return player; }
	std::vector<Chick*>& GetChicks() { return mChicks; }
private:
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	bool mUpdatingActors;
	MapData* mp;
	std::vector<class SpriteComponent*> mSprites;
	Player* player;
	InputManager* input;
	int animcounter;
	int nextStage;
	std::vector<Chick*> mChicks;
	Collision* colManager;
};

#endif
