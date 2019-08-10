#ifndef __MAKEDUNGEON_H__
#define __MAKEDUNGEON_H__

#include"error.h"
#include<vector>
#include<memory>
#include<time.h>

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

//���@��@

//���@��
void mazeDig(vector<vector<RogueLikeMap>>& map_, size_t x_, size_t y_, const size_t id_wall_, const size_t id_empty_)
{
	int32_t dx, dy;
	size_t random = size_t(rand()), counter = 0;
	while (counter < 4) {
		switch ((random + counter) & 3)
		{
		case 0:dx = 0; dy = -2; break;
		case 1:dx = -2; dy = 0; break;
		case 2:dx = 0; dy = 2; break;
		case 3:dx = 2; dy = 0; break;
		default:dx = 0; dy = 0; break;
		}
		if (x_ + dx <= 0 || y_ + dy <= 0 || x_ + dx >= map_.size() - 1 || y_ + dy >= map_.data()->size() - 1 || map_[x_ + dx][y_ + dy].mapData== id_empty_) {
			++counter;
		}
		else if (map_[x_ + dx][y_ + dy].mapData == id_wall_) {
			map_[x_ + (dx >> 1)][y_ + (dy >> 1)] = id_empty_;
			map_[x_ + dx][y_ + dy] = id_empty_;
			x_ += dx;
			y_ += dy;
			counter = 0;
			random = size_t(rand());
		}
	}
	return;
}

//���H����
const size_t mazeMakeLoop(vector<vector<RogueLikeMap>>& map_, const size_t id_wall_, const size_t id_empty_, std::unique_ptr<size_t[]>& select_x, std::unique_ptr<size_t[]>& select_y)
{
	size_t ii = 0;
	const size_t i_max = map_.size() - 1;
	const size_t j_max = map_.data()->size() - 1;

	for (size_t i = 1; i < i_max; i += 2)
		for (size_t j = 1; j < j_max; j += 2) {
			if (map_[i][j].mapData != id_empty_) continue;
			if ((i >= 2 && map_[i - 2][j].mapData == id_wall_) || (j >= 2 && map_[i][j - 2].mapData == id_wall_)) {
				select_x[ii] = i;
				select_y[ii] = j;
				++ii;
			}
			else if ((j == map_.data()->size() - 2) && (i == map_.size() - 2)) break;
			else if ((i + 2 < map_.size() && map_[i + 2][j].mapData == id_wall_) || (j + 2 < map_.data()->size() && map_[i][j + 2].mapData == id_wall_)) {
				select_x[ii] = i;
				select_y[ii] = j;
				++ii;
			}
		}
	return ii;
}
void mazeMake(vector<vector<RogueLikeMap>>& map_, const size_t id_wall_, const size_t id_empty_)
{
	if (map_.size() <= 2 || map_.data()->size() <= 2) return;
	if ((map_.size() & 1) == 0 || (map_.data()->size() & 1) == 0) return;

	map_[1][1] = id_empty_;

	size_t a, ii;
	std::unique_ptr<size_t[]> select_x(new size_t[map_.size() * map_.data()->size()]);
	std::unique_ptr<size_t[]> select_y(new size_t[map_.size() * map_.data()->size()]);

	//���W��I��
	while (true)
	{
		ii = mazeMakeLoop(map_, id_wall_, id_empty_, select_x, select_y);
		if (ii == 0) break;
		srand((unsigned int)time(nullptr));
		a = size_t(rand()) % ii;
		mazeDig(map_, select_x[a], select_y[a], id_wall_, id_empty_);
	}
	return;
}
#endif
