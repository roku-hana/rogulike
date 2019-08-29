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
const size_t MAPX_RLk = 127; //マップ縦サイズ
const size_t MAPY_RLk = 95;   //マップ横サイズ

struct DungeonMap_RL
{

	//生成される部屋の数 (正確に言うと生成される区域の数)
	size_t divCountMin = 7; //マップの区分け最小数
	size_t divCountRand = 4; //マップの区分け数加算

	//生成される部屋のサイズ
	size_t roomLengthMinX = 15; //部屋のX座標の最小サイズ
	size_t roomLengthMinY = 13; //部屋のY座標の最小サイズ
	size_t roomLengthRandX = 2; //部屋のX座標のサイズ加算
	size_t roomLengthRandY = 2; //部屋のY座標のサイズ加算

	size_t mapDivCount{}; //マップの区分け数 (部屋の個数) 0~nまでの部屋ID

	size_t mapDiv[12][4] = {0}; //マップの区域 [部屋ID][X終点 , Y終点 , X始点 , Y始点]
	size_t mapRoom[12][4] = {0}; //マップの部屋 [部屋ID][X終点 , Y終点 , X始点 , Y始点]
	size_t mapRoad[12][4] = {0}; //マップの道 [部屋ID(前)][繋がる先の部屋ID(後) , (0.X座標 , 1.Y座標) , (前)側の通路の位置 , (後)側の通路の位置]
	//size_t mapRoomPlayer[12] = {0};

	size_t count[12] = { 0 };
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
	/*マップ系データ*/
	DungeonMap_RL dng; //ダンジョン
	vector<vector<RogueLikeMap>> maprl;
	vector<vector<int>> transparentMap;
	static int mapchip[3];
	int sx, sy;		//スタートの位置
	int gx, gy;		//ゴールの位置
	vector<int> cx, cy;		//ひよこの位置
	int chickNum;			//ひよこの数
	vector<int> ex, ey;		//敵の位置
	int enemyNum;			//敵の数
	static int stageNum;
	int minDestination;    //startからgoalまでの最短距離
	int BreadthFirstSearch();
	void Decide_Pos();
	//int darkness;
	size_t minx, miny, maxx, maxy;
	size_t addx, addy;
	int lightknd;
	int dirbox;
};
#endif
