#include"testplayer.h"
#include<DxLib.h>
#include"input.h"

TestPlayer::TestPlayer(InputManager* t) : input(t){
	LoadDivGraph("Images\\cat.png", 12, 3, 4, 32, 32, gh);
	x = 320, y = 256;
	scrollx = 96;
	scrolly = 96;
}

void TestPlayer::update() {
	if (ismoving) {
		if (input->isPushRight() && scrollx < 1280) scrollx += 32;
		if (input->isPushLeft() && scrollx > 96) scrollx -= 32;
		if (input->isPushUp() && scrolly > 96) scrolly -= 32;
		if (input->isPushDown() && scrolly < 512) scrolly += 32;
	}
	//if (input->isPushRight() && scrollx >96) scrollx -= 32;
	//if (input->isPushLeft() && scrollx < 1280) scrollx += 32;
	//if (input->isPushUp() && scrolly < 512) scrolly += 32;
	//if (input->isPushDown() && scrolly > 96) scrolly -= 32;

}

void TestPlayer::draw() {
	DrawGraph(x, y, gh[0], TRUE);
	DrawFormatString(400, 20, GetColor(0, 0, 255), "sx:%d, sy:%d", scrollx, scrolly);
}