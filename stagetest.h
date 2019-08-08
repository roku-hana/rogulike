#ifndef __STAGETEST_H__
#define __STAGETEST_H__

#include<vector>
using namespace std;

class TestPlayer;
class InputManager;

enum MAP_KIND{
	WALL,
	ROOM,
	PATH,
	GOAL,
};

class StageTest {
public:
	StageTest(InputManager*);
	~StageTest();
	void draw();
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