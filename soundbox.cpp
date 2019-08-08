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
	if (fp.fail()) MSG("音テキストファイル読み込みエラー")
	while (getline(fp, name)) {
		if ((sh = LoadSoundMem(name.c_str())) == -1) MSG("音ファイル読み込みエラー");
		setSound(sh);
	}
}

//サウンドハンドルの登録
int SoundBox::setSound(int shandle) {
	sounds.push_back(shandle);
	return sounds.size() - 1;
}

//サウンドの再生
void SoundBox::playSound(int snum) {
	PlaySoundMem(sounds.at(snum), DX_PLAYTYPE_BACK);
}

//サウンドの停止
void SoundBox::stopSound(int snum) {
	StopSoundMem(sounds.at(snum));
}

//BGMの再生(現在のBGMは停止)
void SoundBox::playBgm(int snum) {
	int newbgm = sounds.at(snum);
	if (bgm == newbgm) return;
	StopSoundMem(bgm);
	bgm = newbgm;
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}