#include"nameinput.h"
#include<DxLib.h>
#include"input.h"
#include<fstream>
#include<iostream>

NameInput::NameInput(InputManager* temp) : input(temp){
	knd = 1;
	x = 20, y = 20;
	mark = LoadGraph("Images\\mark.png");
	name.clear();
	//loadName();
	i = 0, j = 0;
	index = 0;
}

NameInput::~NameInput() {
	//saveName();
}

void NameInput::update() {
	if (input->isPushRight()) {
		if (j == 5 && k < 4) {
			switch (k) {
			case 0: x += 30; break;
			case 1: x += 60; break;
			case 2: x += 90; break;
			case 3: x += 90; break;
			}
			k++;
		}
		if (j != 5 && i < 12) {
			i++;
			x += 30;
		}
	}
	if (input->isPushLeft()) {
		if (j == 5 && k > 0) {
			switch (k) {
			case 1: x -= 30; break;
			case 2: x -= 60; break;
			case 3: x -= 90; break;
			case 4: x -= 90; break;
			}
			k--;
		}
		if (j != 5 && i > 0) {
			i--;
			x -= 30;
		}
	}
	if (input->isPushUp()) {
		if (j == 5) {
			switch (k) {
			case 0: i = 0; k = 0; break;
			case 1: i = 1; k = 0; break;
			case 2: i = 3; k = 0; break;
			case 3: i = 6; k = 0; break;
			case 4: i = 9; k = 0; break;
			}
		}
		if (j > 0) {
			j--;
			y -= 20;
		}
	}
	if (input->isPushDown()) {
		if (j == 4) {
			if (i == 0) {
				x = 20;
				k = 0;
			}
			if (i > 0 && i <= 2) {
				x = 50;
				k = 1;
			}
			if (i >= 3 && i <= 5) {
				x = 110;
				k = 2;
			}
			if (i >= 6 && i <= 8) {
				x = 200;
				k = 3;
			}
			if (i >= 9 && i <= 12) {
				x = 290;
				k = 4;
			}
		}
		if (j < 5) {
			j++;
			y += 20;
		}
	}
	if (input->isPushB()) {
		if (index < 6 && j < 5) {
			BuildFlag(lastchar[index - 1], i, j);
			Convert_2Point();
			Convert_Maru();
			if (!flag1 && !flag2) {
				switch (knd) {
				case 1: name += hiragana[j * 13 + i]; lastchar[index] = 1; charknd = j * 13 + i; break;
				case 2: name += katakana[j * 13 + i]; lastchar[index] = 2; charknd = j * 13 + i; break;
				case 3: name += alphabet[j * 13 + i]; lastchar[index] = 3;  break;
				default: break;
				}
				index++;
			}
			flag1 = false;
			flag2 = false;
		}
		if (j == 5) {
			switch (k) {
			case 0: knd = 1; setDefault(); break;
			case 1: knd = 2; setDefault(); break;
			case 2: knd = 3; setDefault(); break;
			case 3: DeleteChar(); break;
			case 4: saveName(); break;
			}
		}
	}

	//アルファベットのときとひらがなカタカナのときで消去のやり方を変える必要がある
	if (input->isPushA()) {
		DeleteChar();
	}
}

void NameInput::draw() {
	switch (knd) {
	case 1:		//ひらがな入力画面
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 5; j++) {
				DrawFormatString(20 + i * 30, 20 + j * 20, GetColor(255, 255, 255), "%s", hiragana[j * 13 + i].c_str());
			}
		}
		break;
	case 2:		//カタカナ入力画面
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 5; j++) {
				DrawFormatString(20 + i * 30, 20 + j * 20, GetColor(255, 255, 255), "%s", katakana[j * 13 + i].c_str());
			}
		}
		break;
	case 3:		//アルファベット入力画面
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 5; j++) {
				DrawFormatString(20 + i * 30, 20 + j * 20, GetColor(255, 255, 255), "%s", alphabet[j * 13 + i].c_str());
			}
		}
		break;
	}
	DrawFormatString(200, 200, GetColor(255, 255, 255), "%s", name.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 126);
	if(j != 5) DrawGraph(x, y, mark, TRUE);
	else {
		switch (k) {
		case 0: 
		case 1:
		case 2:
		case 3:
			DrawExtendGraph(x, y, x + 30, y + 15, mark, TRUE); break;
		case 4:
			DrawExtendGraph(x, y, x + 45, y + 15, mark, TRUE); break;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(20, 120, "かな", GetColor(255, 255, 255));
	DrawString(50, 120, "カナ", GetColor(255, 255, 255));
	DrawString(110, 120, "ABC", GetColor(255, 255, 255));
	DrawString(200, 120, "消す", GetColor(255, 255, 255));
	DrawString(290, 120, "おわり", GetColor(255, 255, 255));
	DrawFormatString(300, 300, GetColor(255, 255, 255), "i:%d, j:%d, k:%d", i, j, k);
	//DrawFormatString(400, 400, GetColor(255, 255, 255), "name.size:%d", name.size());
	//if (flag1) DrawString(300, 20, "flag1", GetColor(255, 255, 255));
	//if (flag2) DrawString(300, 50, "flag2", GetColor(255, 255, 255));
	//for(int i = 0; i < 7; i++) DrawFormatString(20 + i * 20, 300, GetColor(255, 255, 255), "%d", lastchar[i]);
	//DrawFormatString(500, 20, GetColor(255, 255, 255), "index:%d", index);
	//DrawFormatString(500, 100, GetColor(255, 255, 255), "charknd:%d", charknd);

}

void NameInput::loadName() {
	ifstream ifs("name.txt");
	if (ifs.fail()) {
		cerr << "Failed to open file." << endl;
		return;
	}
	getline(ifs, name);
}

void NameInput::saveName() {
	ofstream ofs("name.txt");
	ofs << name.c_str() << endl;
}

void NameInput::Convert_2Point() {
	if (flag1) {
		if (lastchar[index-1] == 1) {
			switch (charknd) {
			case 1: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "が"; break;
			case 14: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぎ"; break;
			case 27: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぐ"; break;
			case 40: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "げ"; break;
			case 53: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ご";  break;
			case 2: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ざ";  break;
			case 15: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "じ"; break;
			case 28: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ず"; break;
			case 41: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぜ"; break;
			case 54: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぞ";  break;
			case 3: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "だ"; break;
			case 16: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぢ";  break;
			case 29: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "づ"; break;
			case 42: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "で";  break;
			case 55: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ど"; break;
			case 5: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ば"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "び"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぶ";  break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "べ";  break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぼ";  break;
			default: break;
			}
		}
		if (lastchar[index-1] == 2) {
			switch (charknd) {
			case 1: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ガ"; break;
			case 14: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ギ"; break;
			case 27: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "グ"; break;
			case 40: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ゲ"; break;
			case 53: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ゴ"; break;
			case 2: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ザ"; break;
			case 15: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ジ";  break;
			case 28: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ズ"; break;
			case 41: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ゼ"; break;
			case 54: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ゾ"; break;
			case 3: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ダ";  break;
			case 16: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ヂ"; break;
			case 29: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ヅ"; break;
			case 42: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "デ"; break;
			case 55: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ド";  break;
			case 5:  if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "バ"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ビ"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ブ"; break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ベ"; break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ボ"; break;
			default: break;
			}
		}
	}
}

void NameInput::Convert_Maru() {
	if (flag2) {
		if (lastchar[index-1] == 1) {
			switch (charknd) {
			case 5: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぱ"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぴ"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぷ"; break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぺ"; break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ぽ"; break;
			default: break;
			}
		}
		if (lastchar[index-1] == 2) {
			switch (charknd) {
			case 5: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "パ"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ピ"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "プ"; break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ペ"; break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "ポ"; break;
			default: break;
			}
		}
	}
}

void NameInput::BuildFlag(int knd, int i, int j) {
	if (knd == 1 || knd == 2) {
		if (j == 0 && i == 12) flag1 = true;
		else if (j == 1 && i == 12) flag2 = true;
	}
	if (knd == 0 && name.size() == 0) {
		if (j == 0 && i == 12) flag1 = true;
		else if (j == 1 && i == 12) flag2 = true;
	}
}

void NameInput::setDefault() {
	i = 0;
	j = 0;
	k = 0;
	x = 20;
	y = 20;
}

void NameInput::DeleteChar() {
	if (name.size() > 0) {
		switch (lastchar[index - 1]) {
		case 1:
		case 2:
			name = name.substr(0, name.size() - 2);
			break;
		case 3:	name.pop_back(); break;
		default: break;
		}
		lastchar[index - 1] = 0;
		index--;
	}
}