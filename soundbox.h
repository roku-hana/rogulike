#ifndef __SOUNDBOX_H__
#define __SOUNDBOX_H__

#include<vector>
#include<string>
using namespace std;

class SoundBox {
	static vector<int> sounds;
	static int bgm;
	string name;
public:
	SoundBox();
	static int setSound(int shandle);
	static void playSound(int snum);
	static void stopSound(int snum);
	static void playBgm(int snum);
};

#endif
