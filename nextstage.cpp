#include"nextstage.h"
#include<DxLib.h>
#include"play.h"

NextStage::NextStage(SceneManager* sManager, int num) :
	Scene(sManager) {
	SetFontSize(40);                             //�T�C�Y��20�ɕύX
	SetFontThickness(1);                         //������1�ɕύX
	//ChangeFont, ChangeFontType�͕��ׂ̏d������������p�ɂɎg��Ȃ��ق�������
	ChangeFont("HGS�n�p�p�߯�ߑ�");              //HGS�n�p�p�߯�ߑ̂ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);//�A���`�G�C���A�X���G�b�W�t���t�H���g�ɕύX
	stageNum = num;
	count = GetNowCount();
}

NextStage::~NextStage() {
	SetFontSize(16);
	SetFontThickness(1);
	//ChangeFont, ChangeFontType�͕��ׂ̏d������������p�ɂɎg��Ȃ��ق�������
	ChangeFont("�f�t�H���g");
	ChangeFontType(DX_FONTTYPE_NORMAL);
}

void NextStage::update() {
	if (GetNowCount() - count >= 3000) {		//3�b��������v���C��ʂ֖߂�
		sceneManager->scene = new Game(sceneManager, sceneManager->input);
		delete this;
	}
}

void NextStage::draw() {
	DrawFormatString(250, 200, GetColor(255, 255, 255), "�n��%d�K",stageNum);
}