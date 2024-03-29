#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include<vector>
#include<string>
#include<queue>

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
	void SetMessage(int i, std::string& pl, std::string& en, int val);
	void SetMessageFlag(bool flag) { messageflag = flag; }
	void SetGameOverFlag(bool flag) { gameover = flag; }
	bool GetGameOverFlag() { return gameover; }
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
	bool messageflag;
	std::queue<std::string> message;
	int messagebox;
	std::vector<EnemyParameter> enemyParam;
	int enemyNum;
	int enemyNum2;
	void LoadMessage();
	void DrawMessage();
	void LoadEnemyParam(const char* fileName);
	bool gameover;
	void PlayerKeyInput();
	void EnemyAddTime();
	std::vector<int> eposx;
	std::vector<int> eposy;
};

#endif
