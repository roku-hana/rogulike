#ifndef __STAGETEST_H__
#define __STAGETEST_H__

#include<vector>
using namespace std;

class TestPlayer;

enum MAP_KIND{
	WALL,
	ROOM,
	PATH,
	GOAL,
};

class StageTest {
public:
	StageTest();
	~StageTest();
	void draw(int x, int y);
	void update();
	//vector<std::vector<int>>* getMapData() { return &mapData; }
private:
	vector<vector<int>> mapData;
	static int wall;
	static int floor;
	static int goal;
	TestPlayer* player;
};

#endif