#include"scenemanager.h"
#include"input.h"

SceneManager::SceneManager() {
	input = new InputManager();
}

SceneManager::~SceneManager() {
	delete input;
	delete scene;
}

void SceneManager::update() {
	input->makeInputState();
	scene->update();
}