#include"game.h"
#include"input.h"
#include"play.h"
#include"gamestage.h"

Game::~Game() {
	delete gameScene;
	delete gameStage;
}

GameScene::GameScene(Game* pManager, SceneManager* sManager) :
	gameManager(pManager),
	sceneManager(sManager)
{

}

Game::Game(SceneManager* pManager, InputManager* iManager) :
	Scene(pManager),
	input(iManager) {
	gameStage = new GameStage(input);
	gameScene = new Play(this, sceneManager);
}

