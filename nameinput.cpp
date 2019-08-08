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

	//�A���t�@�x�b�g�̂Ƃ��ƂЂ炪�ȃJ�^�J�i�̂Ƃ��ŏ����̂�����ς���K�v������
	if (input->isPushA()) {
		DeleteChar();
	}
}

void NameInput::draw() {
	switch (knd) {
	case 1:		//�Ђ炪�ȓ��͉��
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 5; j++) {
				DrawFormatString(20 + i * 30, 20 + j * 20, GetColor(255, 255, 255), "%s", hiragana[j * 13 + i].c_str());
			}
		}
		break;
	case 2:		//�J�^�J�i���͉��
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 5; j++) {
				DrawFormatString(20 + i * 30, 20 + j * 20, GetColor(255, 255, 255), "%s", katakana[j * 13 + i].c_str());
			}
		}
		break;
	case 3:		//�A���t�@�x�b�g���͉��
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
	DrawString(20, 120, "����", GetColor(255, 255, 255));
	DrawString(50, 120, "�J�i", GetColor(255, 255, 255));
	DrawString(110, 120, "ABC", GetColor(255, 255, 255));
	DrawString(200, 120, "����", GetColor(255, 255, 255));
	DrawString(290, 120, "�����", GetColor(255, 255, 255));
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
			case 1: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 14: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 27: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 40: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 53: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			case 2: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			case 15: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 28: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 41: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 54: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			case 3: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 16: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			case 29: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 42: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			case 55: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 5: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��";  break;
			default: break;
			}
		}
		if (lastchar[index-1] == 2) {
			switch (charknd) {
			case 1: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�K"; break;
			case 14: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�M"; break;
			case 27: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�O"; break;
			case 40: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�Q"; break;
			case 53: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�S"; break;
			case 2: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�U"; break;
			case 15: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�W";  break;
			case 28: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�Y"; break;
			case 41: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�["; break;
			case 54: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�]"; break;
			case 3: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�_";  break;
			case 16: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�a"; break;
			case 29: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�d"; break;
			case 42: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�f"; break;
			case 55: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�h";  break;
			case 5:  if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�o"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�r"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�u"; break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�x"; break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�{"; break;
			default: break;
			}
		}
	}
}

void NameInput::Convert_Maru() {
	if (flag2) {
		if (lastchar[index-1] == 1) {
			switch (charknd) {
			case 5: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "��"; break;
			default: break;
			}
		}
		if (lastchar[index-1] == 2) {
			switch (charknd) {
			case 5: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�p"; break;
			case 18: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�s"; break;
			case 31: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�v"; break;
			case 44: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�y"; break;
			case 57: if (name.size() > 0) name = name.substr(0, name.size() - 2); name += "�|"; break;
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