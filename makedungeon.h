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

const int PLAYER_POS_X = 320;
const int PLAYER_POS_Y = 224;
const int CHIPSIZE = 32;
const int DRAW_STARTPOS_X = 96;
const int DRAW_STARTPOS_Y = 48;
const int DRAW_CHIPNUM_X = 7;
const int DRAW_CHIPNUM_Y = 6;
const size_t MAPX_RLk = 127; //�}�b�v�c�T�C�Y
const size_t MAPY_RLk = 95;   //�}�b�v���T�C�Y

struct DungeonMap_RL
{

	//��������镔���̐� (���m�Ɍ����Ɛ����������̐�)
	size_t divCountMin = 7; //�}�b�v�̋敪���ŏ���
	size_t divCountRand = 4; //�}�b�v�̋敪�������Z

	//��������镔���̃T�C�Y
	size_t roomLengthMinX = 15; //������X���W�̍ŏ��T�C�Y
	size_t roomLengthMinY = 13; //������Y���W�̍ŏ��T�C�Y
	size_t roomLengthRandX = 2; //������X���W�̃T�C�Y���Z
	size_t roomLengthRandY = 2; //������Y���W�̃T�C�Y���Z

	size_t mapDivCount{}; //�}�b�v�̋敪���� (�����̌�) 0~n�܂ł̕���ID

	size_t mapDiv[12][4] = {0}; //�}�b�v�̋�� [����ID][X�I�_ , Y�I�_ , X�n�_ , Y�n�_]
	size_t mapRoom[12][4] = {0}; //�}�b�v�̕��� [����ID][X�I�_ , Y�I�_ , X�n�_ , Y�n�_]
	size_t mapRoad[12][4] = {0}; //�}�b�v�̓� [����ID(�O)][�q�����̕���ID(��) , (0.X���W , 1.Y���W) , (�O)���̒ʘH�̈ʒu , (��)���̒ʘH�̈ʒu]
	//size_t mapRoomPlayer[12] = {0};

	size_t count[12] = { 0 };
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
	void DrawEnemyPos(int x, int y);
	void DrawTempMap();
	void DrawDarkness(int x, int y);
	int GetStartX() { return sx; }
	int GetStartY() { return sy; }
	int GetGoalX() { return gx; }
	int GetGoalY() { return gy; }
	int GetChickX(int i) { return cx[i]; }
	int GetChickY(int i) { return cy[i]; }
	int GetEnemyX(int i) { return ex[i]; }
	int GetEnemyY(int i) { return ey[i]; }
	int GetChickNum() { return chickNum; }
	int GetEnemyNum() { return enemyNum; }
	int GetStageNum() { return stageNum; }
	vector<vector<RogueLikeMap>>& GetMap() { return maprl; }
	int GetLightKnd() { return lightknd; }
	int* GetDirBox() { return &dirbox; }
	private:
	/*�}�b�v�n�f�[�^*/
	DungeonMap_RL dng; //�_���W����
	vector<vector<RogueLikeMap>> maprl;
	vector<vector<int>> transparentMap;
	static int mapchip[3];
	int sx, sy;		//�X�^�[�g�̈ʒu
	int gx, gy;		//�S�[���̈ʒu
	vector<int> cx, cy;		//�Ђ悱�̈ʒu
	int chickNum;			//�Ђ悱�̐�
	vector<int> ex, ey;		//�G�̈ʒu
	int enemyNum;			//�G�̐�
	static int stageNum;
	int minDestination;    //start����goal�܂ł̍ŒZ����
	int BreadthFirstSearch();
	void Decide_Pos();
	//int darkness;
	size_t minx, miny, maxx, maxy;
	size_t addx, addy;
	int lightknd;
	int dirbox;
};
#endif
