#include"stagetest.h"
#include<DxLib.h>
#include"input.h"

StageTest::StageTest() : mapData(20, vector<int>(45)){	//vectorのメンバー関数はこれで初期化する必要がある
	FILE* fp;
	char ch;
	int i = 0, j = 0;

	/* ファイルのオープン */
	if ((fopen_s(&fp, "tempstage.txt", "r")) != 0) {
		fprintf(stderr, "%sのオープンに失敗しました.\n", "tempstage.txt");
		exit(EXIT_FAILURE);
	}

	/* ファイルの終端まで文字を読み取り表示する */
	while ((ch = fgetc(fp)) != EOF) {
		if (j == 45) {
			j = 0;
			i++;
		}
		mapData[i][j] = atoi(&ch);
		j++;
	}

	/* ファイルのクローズ */
	fclose(fp);

	LoadDivGraph("Images\\640x480\\pipo-map001_at-miti.png", 1, 1, 1, 32, 32, &floor);
	LoadDivGraph("Images\\640x480\\pipo-map001_at-yama2.png", 1, 1, 1, 32, 32, &wall);
	LoadDivGraph("Images\\640x480\\pipo-map001_at-umi.png", 1, 1, 1, 32, 32, &goal);

	//player = new TestPlayer(input);
}

StageTest::~StageTest() {
	//delete player;
}

void StageTest::update() {
	
}

void StageTest::draw(int x, int y) {
	int minx = x / 32 - 3;
	int miny = y / 32 - 3;
	for (int i = y / 32 - 3; i < y / 32 + 3; i++) {
		for (int j = x / 32 - 3; j < x / 32 + 3; j++) {
			switch (mapData[i][j]) {
			case WALL: DrawGraph((j - minx) * 32 + 224, (i - miny) * 32 + 160, wall, TRUE); break;
			case ROOM: DrawGraph((j - minx) * 32 + 224, (i - miny) * 32 + 160, floor, TRUE); break;
			case PATH: DrawGraph((j - minx) * 32 + 224, (i - miny) * 32 + 160, floor, TRUE); break;
			case GOAL: DrawGraph((j - minx) * 32 + 224, (i - miny) * 32 + 160, goal, TRUE); break;
			}
		}
	}
}

int StageTest::floor;
int StageTest::goal;
int StageTest::wall;