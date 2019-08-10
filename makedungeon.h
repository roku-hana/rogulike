#ifndef __MAKEDUNGEON_H__
#define __MAKEDUNGEON_H__

#include"error.h"
#include<vector>

using namespace std;

enum :int {
	RL_COUNT_X,
	RL_COUNT_Y
};

enum MAP_KIND {
	PATH,
	WALL,
	START,
	GOAL,
};

const int CHIPSIZE = 32;
const int DRAW_STARTPOS_X = 160;
const int DRAW_STARTPOS_Y = 96;
const int DRAW_CHIPNUM_X = 5;
const int DRAW_CHIPNUM_Y = 4;

struct DungeonMap_RL
{

	//��������镔���̐� (���m�Ɍ����Ɛ����������̐�)
	size_t divCountMin = 3; //�}�b�v�̋敪���ŏ���
	size_t divCountRand = 4; //�}�b�v�̋敪�������Z

	//��������镔���̃T�C�Y
	size_t roomLengthMinX = 10; //������X���W�̍ŏ��T�C�Y
	size_t roomLengthMinY = 8; //������Y���W�̍ŏ��T�C�Y
	size_t roomLengthRandX = 5; //������X���W�̃T�C�Y���Z
	size_t roomLengthRandY = 5; //������Y���W�̃T�C�Y���Z

	size_t mapDivCount{}; //�}�b�v�̋敪���� (�����̌�) 0~n�܂ł̕���ID

	//8 = divCountMin + divCountRand �Ƃ��āA���I�m�ۂ���΁A�_���W�����̃T�C�Y���D���ɕς����邩������Ȃ�?
	size_t mapDiv[8][4]{}; //�}�b�v�̋�� [����ID][X�I�_ , Y�I�_ , X�n�_ , Y�n�_]
	size_t mapRoom[8][4]{}; //�}�b�v�̕��� [����ID][X�I�_ , Y�I�_ , X�n�_ , Y�n�_]
	size_t mapRoad[8][4]{}; //�}�b�v�̓� [����ID(�O)][�q�����̕���ID(��) , (0.X���W , 1.Y���W) , (�O)���̒ʘH�̈ʒu , (��)���̒ʘH�̈ʒu]
	size_t mapRoomPlayer[8]{};

	size_t startx;
	size_t starty;
	size_t goalx;
	size_t goaly;

};

//�T���v��
class MapData_RL
{
public:
	MapData_RL(const size_t var_) :mapData(var_) {}
	MapData_RL() = default;
	size_t mapData = 1; //�}�b�v
};

//����̃}�b�v�f�[�^�������܂�
class RogueLikeMap
{
public:
	RogueLikeMap(const size_t var_) :mapData(var_) {}
	RogueLikeMap() = default;

	//���������\�ȃ}�b�v
	size_t mapData = 1;

};

class MapData {
public:
	MapData();
	void draw(int x, int y);
	void DrawTransparentMaze(int x, int y);
	void DrawTempMap();
	int GetStartX() { return sx; }
	int GetStartY() { return sy; }
	vector<vector<RogueLikeMap>>& GetMap() { return maprl; }
private:
	/*�}�b�v�n�f�[�^*/
	//�}�b�v�̏c�T�C�Y�Ɖ��T�C�Y�������łȂ��ƃG���[�ɂȂ�
	const size_t MAPX_RLk = 64; //�}�b�v�c�T�C�Y
	const size_t MAPY_RLk = 48;   //�}�b�v���T�C�Y
	DungeonMap_RL dng; //�_���W����
	vector<vector<RogueLikeMap>> maprl;
	vector<vector<int>> transparentMap;
	static int wall;
	static int floor;
	static int goal;
	static int start;  //��ŏ���
	int sx, sy;
	int gx, gy;
};
#endif
