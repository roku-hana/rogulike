#include<Dxlib.h>
#include"scenemanager.h"
#include"input.h"
#include"title.h"
#include"soundbox.h"

//初期ゲーム画面サイズ 縦：480 横：640

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SceneManager* sceneManager = new SceneManager();

	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SoundBox* sound = new SoundBox();
	sceneManager->scene = new Title(sceneManager);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && sceneManager->input->gpUpdateKey() == 0 && sceneManager->input->getStateKey()[KEY_INPUT_ESCAPE] == 0) {
		sceneManager->draw();
		sceneManager->update();
	}


	delete sceneManager;
	delete sound;
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}