#ifndef __NAMEINPUT_H__
#define __NAMEINPUT_H__

#include<string>
using namespace std;

class InputManager;

class NameInput {
public:
	NameInput(InputManager*);
	~NameInput();
	void Convert_2Point();
	void Convert_Maru();
	void update();
	void draw();
	void loadName();
	void saveName();
private:
	int mark;
	int x, y;
	int knd;
	int i, j, k;
	int lastchar[7];		//7�����܂�
	int index;
	InputManager* input;
	bool flag1, flag2;
	int charknd;
	string hiragana[65] = {
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�h",
		"��", "��", "��", "��", "��", "��", "��", "�@", "��", "�@", "��", "��", "�K",
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�[",
		"��", "��", "��", "��", "��", "��", "��", "�@", "��", "�@", "��", "��", "�A",
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�@", "�B"
	};
	string katakana[65] = {
		"�A", "�J", "�T", "�^", "�i", "�n", "�}", "��", "��", "��", "�@", "��", "�h",
		"�C", "�L", "�V", "�`", "�j", "�q", "�~", "�@", "��", "�@", "�B", "��", "�K",
		"�E", "�N", "�X", "�c", "�k", "�t", "��", "��", "��", "��", "�D", "��", "�[",
		"�G", "�P", "�Z", "�e", "�l", "�w", "��", "�@", "��", "�@", "�F", "�b", "�A",
		"�I", "�R", "�\", "�g", "�m", "�z", "��", "��", "��", "��", "�H", "�@", "�B"
	};
	string alphabet[65] = {
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
		"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
		"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", ",", " "
	};
	string name;
	void BuildFlag(int, int, int);
	void setDefault();
	void DeleteChar();
};

#endif
