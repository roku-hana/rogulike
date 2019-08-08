#ifndef __GAME_H__
#define __GAME_H__

#include"scenemanager.h"

//前方宣言
class Game;
class InputManager;
class GameStage;

//ゲームシーンの基底クラス
class GameScene {
protected:
	Game* gameManager;
	SceneManager* sceneManager;
public:
	GameScene(Game* pManager, SceneManager* sManager);
	virtual ~GameScene() {};
	virtual void update() {};
	virtual void draw() {};
};

class Game : public Scene {
public:
	InputManager* input;
	GameScene* gameScene;
	Game(SceneManager*, InputManager*);
	~Game();
	void update() { gameScene->update(); }
	void draw() { gameScene->draw(); }
	GameStage* getGameStage() { return gameStage; }
private:
	GameStage* gameStage;
};

#endif

