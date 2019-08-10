#ifndef __ANIMDRAW_H__
#define __ANIMDRAW_H__

#include<vector>
using namespace std;

enum Direction {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
	NONE
};

class AnimDraw {
private:
	struct animpat {
		vector<int> ghlist;
		int animgap; //�\���Ԋu(���̒l��傫������ƁA�A�j���[�V�������x���Ȃ�A����������Ƒ����Ȃ�)
		animpat() { animgap = 1; }
	};
	vector<animpat> aplist;
public:
	AnimDraw() { aplist.push_back(animpat()); }
	//apid�̓A�j���p�^�[���̔ԍ��A�܂胁���o�ϐ�aplist�̃C���f�b�N�X��\���Ă���
	int SetImage(unsigned int apid, int ghandle);  //�O���t�B�b�N�n���h�����Z�b�g����
	int SetGap(unsigned int apid, int gap);  //�\���Ԋu(animagp)���Z�b�g����
	void DrawAnimation(int apid, int x, int y, int count);  //�A�j���[�V�����\��
	void DrawTurnAnimation(int apid, int x, int y, int count, Direction dir);  //�A�j���[�V�������E���]
	void DrawRotaAnimation(int apid, int x, int y, int count, float rad);  //�A�j���[�V������]�\��
};

#endif
