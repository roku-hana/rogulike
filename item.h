#ifndef __ITEM_H__
#define __ITEM_H__

#include"actor.h"
#include<string>
#include<vector>
using namespace std;

class RogueLikeMap;
struct ItemData;

enum ITEM_KND {
	WEAPON,
	PROTECTION,
	RECOVERY
};

class Item : public Actor {
public:
	Item(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y);
	~Item();
	virtual void Use() {};
	virtual void Off() {};
	void Throw(int px, int py, Direction dir);
	virtual void Put(int px, int py);
	//virtual void Explain() {};
	void updateActor() override;
	int GetPosX() const { return posx; }
	int GetPosY() const { return posy; }
	string GetName() { return name; }
	string GetExplanation() { return explanation; }
	int GetCategory() { return category; }
	bool GetEquip() { return equip; }
protected:
	int id;
	int category;
	int flag;
	string name;
	string explanation;
	int posx, posy;
	const vector<vector<RogueLikeMap>> mapdata;
	int addx, addy;
	bool equip;
private:
	bool isDraw(int x, int y);
	bool throwflag;
	int count;
};

#endif