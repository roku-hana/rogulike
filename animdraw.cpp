#include"animdraw.h"
#include<DxLib.h>

//�O���t�B�b�N�n���h���̃Z�b�g
int AnimDraw::SetImage(unsigned int apid, int ghandle) {
	if (apid >= aplist.size()) {
		aplist.push_back(animpat());  //�V�����A�j���p�^�[���̒ǉ�
		apid = aplist.size() - 1;    //apid���ǉ������A�j���p�^�[�����w���悤�ɒ���
	}
	aplist.at(apid).ghlist.push_back(ghandle);
	return apid;
}

//�A�j���[�V�����M���b�v�̃Z�b�g(1�R�}�̕\���Ԋu)
int AnimDraw::SetGap(unsigned int apid, int gap) {
	if (apid >= aplist.size()) {
		aplist.push_back(animpat());
		apid = aplist.size() - 1;
	}
	aplist.at(apid).animgap = gap;
	return apid;
}

/*����apid�Ŏw�肳�ꂽ�A�j���p�^�[���̉摜����1���Ȃ�A�j���[�V����������K�v�Ȃ��B����āA�P���ɃA�j���p�^�[���̍ŏ��̉摜(ghlist.at(0))��\��
�����̉摜���o�^����Ă���ꍇ�́Aanimcounter �� 1�R�}�̕\���Ԋu % �R�}���̌v�Z�ŕ\�����ׂ��C���f�b�N�X�����߁A���̉摜��\��*/

//�A�j���[�V�����`��
void AnimDraw::DrawAnimation(int apid, int x, int y, bool ismoving) {
	if (aplist.at(apid).ghlist.size() > 1) { //�R�}���̊m�F
		int curpat = 0;
		if (ismoving) curpat = GameStage::getAnimCounter() / aplist.at(apid).animgap % aplist.at(apid).ghlist.size();
		DrawGraph(x, y, aplist.at(apid).ghlist.at(curpat), TRUE);
	}
	else {
		DrawGraph(x, y, aplist.at(apid).ghlist.at(0), TRUE);
	}
}

//�A�j���[�V�������E(�㉺)���]�`��
void AnimDraw::DrawTurnAnimation(int apid, int x, int y, Direction dir) {
	if (aplist.at(apid).ghlist.size() > 1) { //�R�}���̊m�F
		int curpat = GameStage::getAnimCounter() / aplist.at(apid).animgap % aplist.at(apid).ghlist.size();
		if (dir == RIGHT || dir == DOWN) DrawGraph(x, y, aplist.at(apid).ghlist.at(curpat), true);
		if (dir == LEFT || dir == UP) DrawTurnGraph(x, y, aplist.at(apid).ghlist.at(curpat), true);
	}
	else {
		DrawGraph(x, y, aplist.at(apid).ghlist.at(0), true);
	}
}

//�A�j���[�V������]�`��
void AnimDraw::DrawRotaAnimation(int apid, int x, int y, float rad) {
	if (aplist.at(apid).ghlist.size() > 1) {
		int curpat = GameStage::getAnimCounter() / aplist.at(apid).animgap % aplist.at(apid).ghlist.size();
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).ghlist.at(curpat), TRUE, FALSE);
	}
	else {
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).ghlist.at(0), TRUE, FALSE);
	}
}