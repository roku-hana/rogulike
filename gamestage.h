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
class Enemy;
struct EnemyParameter;

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
	void AddEnemy(Enemy* enemy);
	void RemoveEnemy(Enemy* enemy);
	void ProcessInput();
	int NextStage() { return nextStage; }
	MapData* GetMapData() { return mp; }
	Player* GetPlayer() { return player; }
	std::vector<Enemy*>* GetEnemies() { return &mEnemies; }
	std::vector<Chick*>& GetChicks() { return mChicks; }
	void SetChickGraphic(int gh) { chickGh = gh; }
	std::string& Get_Message(int i, std::string& pl, std::string& en, int val);
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
	std::vector<Enemy*> mEnemies;
	Collision* colManager;
	int chickGh;
	std::vector<std::string> messages;
	std::string message;
	std::vector<EnemyParameter> enemyParam;
	int enemyNum;
	void LoadMessage();
	void LoadEnemyParam(const char* fileName);
};

#endif
