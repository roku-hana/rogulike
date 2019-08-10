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

	//生成される部屋の数 (正確に言うと生成される区域の数)
	size_t divCountMin = 3; //マップの区分け最小数
	size_t divCountRand = 4; //マップの区分け数加算

	//生成される部屋のサイズ
	size_t roomLengthMinX = 10; //部屋のX座標の最小サイズ
	size_t roomLengthMinY = 8; //部屋のY座標の最小サイズ
	size_t roomLengthRandX = 5; //部屋のX座標のサイズ加算
	size_t roomLengthRandY = 5; //部屋のY座標のサイズ加算

	size_t mapDivCount{}; //マップの区分け数 (部屋の個数) 0~nまでの部屋ID

	//8 = divCountMin + divCountRand として、動的確保すれば、ダンジョンのサイズを好きに変えられるかもしれない?
	size_t mapDiv[8][4]{}; //マップの区域 [部屋ID][X終点 , Y終点 , X始点 , Y始点]
	size_t mapRoom[8][4]{}; //マップの部屋 [部屋ID][X終点 , Y終点 , X始点 , Y始点]
	size_t mapRoad[8][4]{}; //マップの道 [部屋ID(前)][繋がる先の部屋ID(後) , (0.X座標 , 1.Y座標) , (前)側の通路の位置 , (後)側の通路の位置]
	size_t mapRoomPlayer[8]{};

	size_t startx;
	size_t starty;
	size_t goalx;
	size_t goaly;

};

//サンプル
class MapData_RL
{
public:
	MapData_RL(const size_t var_) :mapData(var_) {}
	MapData_RL() = default;
	size_t mapData = 1; //マップ
};

//自作のマップデータを扱えます
class RogueLikeMap
{
public:
	RogueLikeMap(const size_t var_) :mapData(var_) {}
	RogueLikeMap() = default;

	//書き換え可能なマップ
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
	/*マップ系データ*/
	//マップの縦サイズと横サイズが同じでないとエラーになる
	const size_t MAPX_RLk = 64; //マップ縦サイズ
	const size_t MAPY_RLk = 48;   //マップ横サイズ
	DungeonMap_RL dng; //ダンジョン
	vector<vector<RogueLikeMap>> maprl;
	vector<vector<int>> transparentMap;
	static int wall;
	static int floor;
	static int goal;
	static int start;  //後で消す
	int sx, sy;
	int gx, gy;
};
#endif
