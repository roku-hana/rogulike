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
class Item;
struct EnemyParameter;

struct ItemData {
	int id;
	std::string name;
	std::string explanation;
	int category;
	int val;
	int probability;
};

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
	void AddItem(Item* item);
	void RemoveItem(Item* item);
	void ProcessInput();
	int NextStage() { return nextStage; }
	MapData* GetMapData() { return mp; }
	Player* GetPlayer() { return player; }
	std::vector<Enemy*>* GetEnemies() { return &mEnemies; }
	std::vector<Chick*>& GetChicks() { return mChicks; }
	std::vector<Item*>& GetItems() { return mItems; }
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
	std::vector<Item*> mItems;
	Collision* colManager;
	int chickGh;
	std::vector<std::string> messages;
	bool messageflag;
	std::queue<std::string> message;
	int messagebox;
	std::vector<EnemyParameter> enemyParam;
	std::vector<ItemData> weapondata;
	std::vector<ItemData> protectiondata;
	std::vector<ItemData> recoverydata;
	int enemyNum;
	int enemyNum2;
	int wNum, pNum, rNum;
	void LoadMessage();
	void DrawMessage();
	void LoadEnemyParam(const char* fileName);
	void LoadProtectionItem(const char* fileName);
	void LoadRecoveryItem(const char* fileName);
	void LoadWeaponItem(const char* fileName);
	bool gameover;
	void PlayerKeyInput();
	void EnemyAddTime();
	std::vector<int> eposx;
	std::vector<int> eposy;
	static bool PlayerEnemyDisComp(const Enemy* a, const Enemy* b);
	void InitializeEnemy();
	void InitializeItem();
};

#endif
