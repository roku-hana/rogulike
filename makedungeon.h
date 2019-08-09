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

struct DungeonMap_RL
{

	//生成される部屋の数 (正確に言うと生成される区域の数)
	size_t divCountMin = 3; //マップの区分け最小数
	size_t divCountRand = 4; //マップの区分け数加算

	//生成される部屋のサイズ
	size_t roomLengthMinX = 5; //部屋のX座標の最小サイズ
	size_t roomLengthMinY = 5; //部屋のY座標の最小サイズ
	size_t roomLengthRandX = 2; //部屋のX座標のサイズ加算
	size_t roomLengthRandY = 2; //部屋のY座標のサイズ加算

	size_t mapDivCount{}; //マップの区分け数 (部屋の個数) 0~nまでの部屋ID
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

	size_t GetMapData() { return mapData; }
};

class MapData {
public:
	MapData();
	void draw(int x, int y);
	int GetStartX() { return sx; }
	int GetStartY() { return sy; }
private:
	/*マップ系データ*/
	const size_t MAPX_RLk = 50; //マップ縦サイズ
	const size_t MAPY_RLk = 50;   //マップ横サイズ
	DungeonMap_RL dng; //ダンジョン
	vector<vector<RogueLikeMap>> maprl;
	static int wall;
	static int floor;
	static int goal;
	static int start;  //後で消す
	int sx, sy;
	int gx, gy;
	const int CHIPSIZE = 32;
};
#endif
