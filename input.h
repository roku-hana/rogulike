#ifndef __INPUT_H__
#define __INPUT_H__

const int KEY_NUM = 256;

class InputManager {
public:
	enum {
		PAD_UP,
		PAD_DOWN,
		PAD_LEFT,
		PAD_RIGHT,
		PAD_BUTTON_B,			//決定orジャンプ
		PAD_BUTTON_A,			//戻る
		PAD_BUTTON_Y,			//shot1
		PAD_BUTTON_R,			//shot2
		PAD_BUTTON_L,			//shot3
		PAD_BUTTON_START,		//メニュー画面へ
		PAD_BUTTON_X,
		PAD_BUTTON_BACK,
		PAD_BUTTON_NUM,
	};
	struct PadKnd {
		int up, down, left, right;
		int a, b, x, y, r, l, start, back;
	};
private:
	int stateKey[KEY_NUM];
	int padInput[PAD_BUTTON_NUM];
	int input;
	int memInput;
	PadKnd padKnd;
public:
	InputManager();
	~InputManager();
	int gpUpdateKey();
	int* getStateKey();
	void setPadInput(PadKnd pad);
	int getPadButtonNum(int button);
	int getPadButton(int button);
	void makeInputState();
	void memoryInput();
	int getInputState() { return input; }
	PadKnd* getPadKnd() { return &padKnd; }
	bool isPushUp(int memory = -1);
	bool isPushDown(int memory = -1);
	bool isPushRight(int memory = -1);
	bool isPushLeft(int memory = -1);
	bool isPushB(int memory = -1);
	bool isPushA(int memory = -1);
	bool isPushX(int memory = -1);
	bool isPushY(int memory = -1);
	bool isPushR(int memory = -1);
	bool isPushL(int memory = -1);
	bool isPushStart(int memory = -1);
	bool isPushBack(int memory = -1);
};

#endif
