#include"soundbox.h"
#include<DxLib.h>
#include<fstream>
#include<sstream>
#include"error.h"

vector<int> SoundBox::sounds;
int SoundBox::bgm = -1;

SoundBox::SoundBox() {
	int sh;
	ifstream fp("Sounds\\sounds.txt");
	if (fp.fail()) MSG("���e�L�X�g�t�@�C���ǂݍ��݃G���[")
	while (getline(fp, name)) {
		if ((sh = LoadSoundMem(name.c_str())) == -1) MSG("���t�@�C���ǂݍ��݃G���[");
		setSound(sh);
	}
}

//�T�E���h�n���h���̓o�^
int SoundBox::setSound(int shandle) {
	sounds.push_back(shandle);
	return sounds.size() - 1;
}

//�T�E���h�̍Đ�
void SoundBox::playSound(int snum) {
	PlaySoundMem(sounds.at(snum), DX_PLAYTYPE_BACK);
}

//�T�E���h�̒�~
void SoundBox::stopSound(int snum) {
	StopSoundMem(sounds.at(snum));
}

//BGM�̍Đ�(���݂�BGM�͒�~)
void SoundBox::playBgm(int snum) {
	int newbgm = sounds.at(snum);
	if (bgm == newbgm) return;
	StopSoundMem(bgm);
	bgm = newbgm;
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}