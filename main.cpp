#include<Dxlib.h>
#include"scenemanager.h"
#include"input.h"
#include"title.h"
#include"soundbox.h"

//�����Q�[����ʃT�C�Y �c�F480 ���F640

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SceneManager* sceneManager = new SceneManager();

	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	SoundBox* sound = new SoundBox();
	sceneManager->scene = new Title(sceneManager);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && sceneManager->input->gpUpdateKey() == 0 && sceneManager->input->getStateKey()[KEY_INPUT_ESCAPE] == 0) {
		sceneManager->draw();
		sceneManager->update();
	}


	delete sceneManager;
	delete sound;
	DxLib_End(); // DX���C�u�����I������
	return 0;
}