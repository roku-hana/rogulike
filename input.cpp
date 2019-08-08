#include"input.h"
#include<DxLib.h>

InputManager::InputManager() : input(0), memInput(0) {
	padKnd.a = PAD_INPUT_A;
	padKnd.b = PAD_INPUT_B;
	padKnd.l = PAD_INPUT_5;
	padKnd.r = PAD_INPUT_6;
	padKnd.x = PAD_INPUT_3;
	padKnd.y = PAD_INPUT_4;
	padKnd.up = PAD_INPUT_UP;
	padKnd.start = PAD_INPUT_8;
	padKnd.back = PAD_INPUT_7;
	padKnd.down = PAD_INPUT_DOWN;
	padKnd.left = PAD_INPUT_LEFT;
	padKnd.right = PAD_INPUT_RIGHT;
	setPadInput(padKnd);
}

InputManager::~InputManager() {

}

int InputManager::gpUpdateKey() {
	char tmpKey[KEY_NUM];

	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < KEY_NUM; i++) {
		if (tmpKey[i] != 0) stateKey[i]++;
		else stateKey[i] = 0;
	}

	return 0;
}

int* InputManager::getStateKey() {
	return stateKey;
}

void InputManager::setPadInput(PadKnd pad) {
	padInput[PAD_UP] = pad.up;
	padInput[PAD_DOWN] = pad.down;
	padInput[PAD_RIGHT] = pad.right;
	padInput[PAD_LEFT] = pad.left;
	padInput[PAD_BUTTON_B] = pad.b;
	padInput[PAD_BUTTON_A] = pad.a;
	padInput[PAD_BUTTON_X] = pad.x;
	padInput[PAD_BUTTON_Y] = pad.y;
	padInput[PAD_BUTTON_L] = pad.l;
	padInput[PAD_BUTTON_R] = pad.r;
	padInput[PAD_BUTTON_START] = pad.start;
	padInput[PAD_BUTTON_BACK] = pad.back;
}

int InputManager::getPadButtonNum(int button) {
	if (button <= PAD_RIGHT || button >= PAD_BUTTON_NUM) return -1;
	//\ŽšƒL[‚Í”ñ‘Î‰ž
	int pad = padInput[button] >> 3;
	int count = 0;
	while (pad != (1 << count)) count++;
	return count;
}

int InputManager::getPadButton(int button) {
	return padInput[button];
}

void InputManager::makeInputState() {
	memInput = input;
	input = GetJoypadInputState(DX_INPUT_PAD1);

	if (stateKey[KEY_INPUT_UP]) input |= padInput[PAD_UP];
	if (stateKey[KEY_INPUT_DOWN]) input |= padInput[PAD_DOWN];
	if (stateKey[KEY_INPUT_RIGHT]) input |= padInput[PAD_RIGHT];
	if (stateKey[KEY_INPUT_LEFT]) input |= padInput[PAD_LEFT];
	if (stateKey[KEY_INPUT_A]) input |= padInput[PAD_BUTTON_Y];
	if (stateKey[KEY_INPUT_S]) input |= padInput[PAD_BUTTON_R];
	if (stateKey[KEY_INPUT_D]) input |= padInput[PAD_BUTTON_L];
	if (stateKey[KEY_INPUT_F]) input |= padInput[PAD_BUTTON_X];
	if (stateKey[KEY_INPUT_SPACE]) input |= padInput[PAD_BUTTON_B];
	if (stateKey[KEY_INPUT_Z]) input |= padInput[PAD_BUTTON_A];
	if (stateKey[KEY_INPUT_X]) input |= padInput[PAD_BUTTON_START];
	if (stateKey[KEY_INPUT_F]) input |= padInput[PAD_BUTTON_BACK];
}

void InputManager::memoryInput() {
	memInput = input;
}

bool InputManager::isPushUp(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_UP] && !(memory & padInput[PAD_UP])) return true;
	else return false;
}

bool InputManager::isPushDown(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_DOWN] && !(memory & padInput[PAD_DOWN])) return true;
	else return false;
}

bool InputManager::isPushRight(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_RIGHT] && !(memory & padInput[PAD_RIGHT])) return true;
	else return false;
}

bool InputManager::isPushLeft(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_LEFT] && !(memory & padInput[PAD_LEFT])) return true;
	else return false;
}

bool InputManager::isPushA(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_BUTTON_A] && !(memory & padInput[PAD_BUTTON_A])) return true;
	else return false;
}

bool InputManager::isPushB(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_BUTTON_B] && !(memory & padInput[PAD_BUTTON_B])) return true;
	else return false;
}

bool InputManager::isPushX(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_BUTTON_X] && !(memory & padInput[PAD_BUTTON_X])) return true;
	else return false;
}

bool InputManager::isPushY(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_BUTTON_Y] && !(memory & padInput[PAD_BUTTON_Y])) return true;
	else return false;
}

bool InputManager::isPushR(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_BUTTON_R] && !(memory & padInput[PAD_BUTTON_R])) return true;
	else return false;
}

bool InputManager::isPushL(int memory) {
	if (memory == -1) memory = memInput;
	if (input & padInput[PAD_BUTTON_L] && !(memory & padInput[PAD_BUTTON_L])) return true;
	else return false;
}

bool InputManager::isPushStart(int memory) {
	if (input & padInput[PAD_BUTTON_START] && !(memory & padInput[PAD_BUTTON_START])) return true;
	else return false;
}

bool InputManager::isPushBack(int memory) {
	if (input & padInput[PAD_BUTTON_BACK] && !(memory & padInput[PAD_BUTTON_BACK])) return true;
	else return false;
}