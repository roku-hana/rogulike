#include "makedungeon.h"
#include<DxLib.h>

int GetRandomNum(int a, int b) {
	return GetRand(b - a) + a;
}

/*ローグライク生成関数*/
template <typename T>
int rogueLikeMapMake(DungeonMap_RL* const dng, T& maprl)
{
	if (maprl.size() == 0 || maprl.front().size() == 0) return -1;
	for (size_t i = 0; i < maprl.size(); ++i)
		for (size_t j = 0; j < maprl[i].size(); ++j)
			maprl[i][j].mapData = 1;

	dng->mapDivCount = dng->divCountMin + (size_t)GetRand((int)dng->divCountRand) + 1; //マップの区分け数 (部屋の個数) 0~nまでの部屋ID
	if (dng->mapDivCount > dng->divCountMin + dng->divCountRand) return -1;

	dng->mapDiv[0][0] = (maprl.size() - 1); //マップの区分け初期サイズX終点 (マップの大きさX軸)
	dng->mapDiv[0][1] = (maprl.front().size() - 1); //マップの区分け初期サイズY終点 (マップの大きさY軸)
	dng->mapDiv[0][2] = 1; //マップの区分け初期サイズX始点 (マップの大きさX軸)
	dng->mapDiv[0][3] = 1; //マップの区分け初期サイズY始点 (マップの大きさY軸)

	dng->mapRoad[0][0] = 255;
	dng->mapRoad[0][1] = 255;

	/*マップを区分けしていく処理(区域を分割する処理)*/
	size_t divAfter;
	int count; //(0:X, 1:Y) X軸で分けるかY軸で分けるか決める

	for (size_t i = 1; i < dng->mapDivCount; ++i) {

		//今まで作った区分けをランダムに指定(指定した区域をさらに区分けする)
		divAfter = (size_t)GetRand((int)i - 1);

		//指定した区域のXとYの長さによって、分割する向きを決める(長いほうを分割する)
		if (dng->mapDiv[divAfter][0] - dng->mapDiv[divAfter][2] > dng->mapDiv[divAfter][1] - dng->mapDiv[divAfter][3]) count = RL_COUNT_X;
		else count = RL_COUNT_Y;

		if (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2] < dng->divCountRand * 2 + 8) {
			size_t k = 0;
			for (size_t j = 1; j < dng->mapDivCount; ++j) {
				if (dng->mapDiv[j][0] - dng->mapDiv[j][2] > k) {
					k = dng->mapDiv[j][0] - dng->mapDiv[j][2];
					divAfter = j;
					count = RL_COUNT_X;
				}
				if (dng->mapDiv[j][1] - dng->mapDiv[j][3] > k) {
					k = dng->mapDiv[j][1] - dng->mapDiv[j][3];
					divAfter = j;
					count = RL_COUNT_Y;
				}
			}
		}

		dng->mapRoad[i][0] = divAfter;
		dng->mapRoad[i][1] = count;

		for (size_t j = 1; j < i; ++j)
			if (dng->mapRoad[j][0] == divAfter) dng->mapRoad[j][0] = i;

		//count軸の設定
		dng->mapDiv[i][count] = dng->mapDiv[divAfter][count + 2] + (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3 + (size_t)GetRand((int)((dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3)); //0.軸の右端(iR)の座標(divAfter*R/3~2divAfter*R/3)
		dng->mapDiv[i][count + 2] = dng->mapDiv[divAfter][count + 2]; //0.軸の左端(iL)の座標(divAfterL)
		dng->mapDiv[divAfter][count + 2] = dng->mapDiv[i][count]; //divAfter軸の左端(divAfterL)の座標(iR)

		//countとは逆の軸の設定
		dng->mapDiv[i][abs(count - 1)] = dng->mapDiv[divAfter][abs(count - 1)]; //軸の右端(iR)の座標(divAfterR)
		dng->mapDiv[i][abs(count - 1) + 2] = dng->mapDiv[divAfter][abs(count - 1) + 2]; //軸の左端(iL)の座標(divAfterL)
	}
	
	/*部屋を生成する処理*/
	for (size_t i = 0; i < dng->mapDivCount; ++i) {//区分け
		dng->mapRoomPlayer[i] = 0;//プレイヤー侵入初期化
		dng->mapRoom[i][2] = dng->mapDiv[i][2]; //区分けX始点をマップX始点へ代入
		dng->mapRoom[i][3] = dng->mapDiv[i][3]; //区分けY始点をマップY始点へ代入

		//X座標の部屋の長さを指定
		//dng->mapRoom[i][0] = dng->mapDiv[i][2] + dng->divCountRand + (size_t)GetRand((int)dng->roomLengthRandX);
		dng->mapRoom[i][0] = dng->mapDiv[i][2] + dng->roomLengthMinX + (size_t)GetRand((int)dng->roomLengthRandX);
		if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
			dng->mapRoom[i][0] = dng->mapDiv[i][0] - 4;
			if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
				dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			}
		}

		dng->mapRoom[i][1] = dng->mapDiv[i][3] + dng->roomLengthMinY + (size_t)GetRand((int)dng->roomLengthRandY);
		if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
			dng->mapRoom[i][1] = dng->mapDiv[i][1] - 4;
			if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
				dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
			}
		}

		if (dng->mapRoom[i][0] - dng->mapDiv[i][2] <= 1 || dng->mapRoom[i][1] - dng->mapDiv[i][3] <= 1) {
			dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
		}
		size_t l = (size_t)GetRand((int)(dng->mapDiv[i][0] - dng->mapRoom[i][0] - 5)) + 2;
		size_t m = (size_t)GetRand((int)(dng->mapDiv[i][1] - dng->mapRoom[i][1] - 5)) + 2;
		dng->mapRoom[i][0] += l;
		dng->mapRoom[i][2] += l;
		dng->mapRoom[i][1] += m;
		dng->mapRoom[i][3] += m;

		for (size_t j = dng->mapRoom[i][2]; j < dng->mapRoom[i][0]; ++j) {
			for (size_t k = dng->mapRoom[i][3]; k < dng->mapRoom[i][1]; ++k) {
				maprl[j][k].mapData = 0;
			}
		}
	}

	/*通路を生成する処理*/
	/*通路は２部屋間の細い道のことを指す。
	通路を作るために２部屋をそれぞれ前(Before)と後(After)で分ける。
	for文で全ての部屋をチェックし、前後の部屋を繋ぐ通路を作る。
	まず、前の通路を作り、次に後の通路を作る。
	最後に前と後の通路を繋げる。
	*/
	size_t roomAfter;
	for (size_t roomBefore = 0; roomBefore < dng->mapDivCount; ++roomBefore) {
		roomAfter = dng->mapRoad[roomBefore][0];

		//X座標の通路
		switch (dng->mapRoad[roomBefore][1]) {
		case RL_COUNT_X:
			dng->mapRoad[roomBefore][2] = (size_t)GetRand((int)(dng->mapRoom[roomBefore][1] - dng->mapRoom[roomBefore][3] - 2)); //前側の通路の位置
			dng->mapRoad[roomBefore][3] = (size_t)GetRand((int)(dng->mapRoom[roomAfter][1] - dng->mapRoom[roomAfter][3] - 2)); //後側の通路の位置
																																	 //前の通路
			for (size_t j = dng->mapRoom[roomBefore][0]; j < dng->mapDiv[roomBefore][0]; ++j)
				maprl[j][dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]].mapData = 0; //通路をマップチップに線画

			//後の通路
			for (size_t j = dng->mapDiv[roomAfter][2]; j < dng->mapRoom[roomAfter][2]; ++j)
				maprl[j][dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]].mapData = 0; //通路をマップチップに線画

			//通路をつなぐ
			for (size_t j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; ++j)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //通路をマップチップに線画 2から5(上から下)
			for (size_t j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; ++j)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //通路をマップチップに線画 5から2(下から上)
			break;

		case RL_COUNT_Y:
			dng->mapRoad[roomBefore][2] = (size_t)GetRand((int)(dng->mapRoom[roomBefore][0] - dng->mapRoom[roomBefore][2] - 2)); //前側の通路の位置
			dng->mapRoad[roomBefore][3] = (size_t)GetRand((int)(dng->mapRoom[roomAfter][0] - dng->mapRoom[roomAfter][2] - 2)); //後側の通路の位置
																																	 //前の通路
			for (size_t j = dng->mapRoom[roomBefore][1]; j < dng->mapDiv[roomBefore][1]; ++j)
				maprl[dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]][j].mapData = 0; //通路をマップチップに線画

			//後の通路
			for (size_t j = dng->mapDiv[roomAfter][3]; j < dng->mapRoom[roomAfter][3]; ++j)
				maprl[dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]][j].mapData = 0; //通路をマップチップに線画

			//通路をつなぐ
			for (size_t j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; ++j)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //通路をマップチップに線画
			for (size_t j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; ++j)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //通路をマップチップに線画
			break;
		}

	}

	//スタート、ゴール位置設定
	int div;
	if (dng->mapDivCount > 0) div = dng->mapDivCount - 1;
	else div = dng->mapDivCount;
	dng->starty = GetRandomNum(dng->mapRoom[0][2], dng->mapRoom[0][0] - 1);
	dng->startx = GetRandomNum(dng->mapRoom[0][3], dng->mapRoom[0][1] - 1);
	dng->goaly = GetRandomNum(dng->mapRoom[div][2], dng->mapRoom[div][0] - 1);
	dng->goalx = GetRandomNum(dng->mapRoom[div][3], dng->mapRoom[div][1] - 1);
	maprl[dng->starty][dng->startx] = 2;
	maprl[dng->goaly][dng->goalx] = 3;
	return 0;
}

MapData::MapData()
	:maprl(MAPY_RLk, vector<RogueLikeMap>(MAPX_RLk, 0)),
	transparentMap(MAPY_RLk, vector<int>(MAPX_RLk, 0)){
	//ダンジョン生成
	while (rogueLikeMapMake(&dng, maprl));

	//後で画像差し替える
	if (floor == 0) {
		LoadDivGraph("Images\\640x480\\pipo-map001_at-miti.png", 1, 1, 1, 32, 32, &floor);
		LoadDivGraph("Images\\640x480\\pipo-map001_at-yama2.png", 1, 1, 1, 32, 32, &wall);
		LoadDivGraph("Images\\640x480\\pipo-map001_at-umi.png", 1, 1, 1, 32, 32, &goal);
		LoadDivGraph("Images\\640x480\\pipo-map001_at-mori.png", 1, 1, 1, 32, 32, &start);
	}
	sx = dng.startx;
	sy = dng.starty;
	gx = dng.goalx;
	gy = dng.goaly;
}

void MapData::draw(int x, int y) {
	size_t minx = x / CHIPSIZE - DRAW_CHIPNUM_X;
	size_t miny = y / CHIPSIZE - DRAW_CHIPNUM_Y;
	size_t maxx = x / CHIPSIZE + DRAW_CHIPNUM_X;
	size_t maxy = y / CHIPSIZE + DRAW_CHIPNUM_Y;
	for (size_t i = miny; i < maxy; ++i) {
		for (size_t j = minx; j < maxx; ++j) {
			size_t kind = maprl[i][j].mapData;
			int posy = i - miny;
			int posx = j - minx;
			switch (kind) {
			case WALL: DrawGraph(DRAW_STARTPOS_X + posx * CHIPSIZE, DRAW_STARTPOS_Y + posy * CHIPSIZE, wall, TRUE); break;
			case PATH: DrawGraph(DRAW_STARTPOS_X + posx * CHIPSIZE, DRAW_STARTPOS_Y + posy * CHIPSIZE, floor, TRUE); break;
			case START: DrawGraph(DRAW_STARTPOS_X + posx * CHIPSIZE, DRAW_STARTPOS_Y + posy * CHIPSIZE, start, TRUE); break;
			case GOAL: DrawGraph(DRAW_STARTPOS_X + posx * CHIPSIZE, DRAW_STARTPOS_Y + posy * CHIPSIZE, goal, TRUE); break;
		}
		}
	}

}

void MapData::DrawTransparentMaze(int x, int y) {
	//プレイヤーがすでに通った場所をチェックする
	transparentMap[y][x] = 10;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	for (size_t y = 0; y < MAPY_RLk; y++) {
		for (size_t x = 0; x < MAPX_RLk; x++) {
			if (transparentMap[y][x] == 10) DrawBox(x * 10, y * 10, x * 10 + 10, y * 10 + 10, GetColor(0, 0, 255), TRUE);
		}
	}
	DrawBox(x * 10, y * 10, x * 10 + 10, y * 10 + 10, GetColor(0, 0, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MapData::DrawTempMap() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	for (size_t y = 0; y < MAPY_RLk; y++) {
		for (size_t x = 0; x < MAPX_RLk; x++) {
			size_t kind = maprl[y][x].mapData;
			switch (kind) {
			case WALL: DrawBox(x * 10, y * 10, x * 10 + 10, y * 10 + 10, GetColor(255, 255, 0), TRUE); break;
			case GOAL: DrawBox(x * 10, y * 10, x * 10 + 10, y * 10 + 10, GetColor(255, 0, 0), TRUE); break;
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int MapData::floor;
int MapData::wall;
int MapData::goal;
int MapData::start;
