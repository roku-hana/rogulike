#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

class MapData;

class GameStage {
public:
	GameStage();
	~GameStage();
	void update();
	void draw();
private:
	MapData* mp;
};

#endif
