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
	//ここ後で、Actorをエネミークラスに変える
	void AddEnemy(Actor* enemy);
	void RemoveEnemy(Actor* enemy);
	//
	void ProcessInput();
	int NextStage() { return nextStage; }
	MapData* GetMapData() { return mp; }
	Player* GetPlayer() { return player; }
	std::vector<Chick*>& GetChicks() { return mChicks; }
	void SetChickGraphic(int gh) { chickGh = gh; }
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
	//ここ後で、エネミークラスを作ってまとめる
	std::vector<Actor*> mEnemies;
	//
	Collision* colManager;
	int chickGh;
};

#endif
