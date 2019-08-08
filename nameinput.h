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
	int lastchar[7];		//7文字まで
	int index;
	InputManager* input;
	bool flag1, flag2;
	int charknd;
	string hiragana[65] = {
		"あ", "か", "さ", "た", "な", "は", "ま", "や", "ら", "わ", "ぁ", "ゃ", "”",
		"い", "き", "し", "ち", "に", "ひ", "み", "　", "り", "　", "ぃ", "ゅ", "゜",
		"う", "く", "す", "つ", "ぬ", "ふ", "む", "ゆ", "る", "を", "ぅ", "ょ", "ー",
		"え", "け", "せ", "て", "ね", "へ", "め", "　", "れ", "　", "ぇ", "っ", "、",
		"お", "こ", "そ", "と", "の", "ほ", "も", "よ", "ろ", "ん", "ぉ", "　", "。"
	};
	string katakana[65] = {
		"ア", "カ", "サ", "タ", "ナ", "ハ", "マ", "ヤ", "ラ", "ワ", "ァ", "ャ", "”",
		"イ", "キ", "シ", "チ", "ニ", "ヒ", "ミ", "　", "リ", "　", "ィ", "ュ", "゜",
		"ウ", "ク", "ス", "ツ", "ヌ", "フ", "ム", "ユ", "ル", "ヲ", "ゥ", "ョ", "ー",
		"エ", "ケ", "セ", "テ", "ネ", "ヘ", "メ", "　", "レ", "　", "ェ", "ッ", "、",
		"オ", "コ", "ソ", "ト", "ノ", "ホ", "モ", "ヨ", "ロ", "ン", "ォ", "　", "。"
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
