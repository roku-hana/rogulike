#ifndef __TESTPLAYER_H__
#define __TESTPLAYER_H__

class InputManager;

class TestPlayer {
public:
	TestPlayer(InputManager*);
	~TestPlayer() {};
	void update();
	void draw();
	int getScrollX() { return scrollx; }
	int getScrollY() { return scrolly; }
	void canMove(bool flag) { ismoving = flag; }
private:
	int gh[12];
	int x, y;
	int scrollx, scrolly;
	InputManager* input;
	bool ismoving;
};

#endif