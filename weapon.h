#ifndef __WEAPON_H__
#define __WEAPON_H__

#include"item.h"

class Weapon : public Item {
public:
	Weapon(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, ItemData* id);
	~Weapon();
	void Use() override;
	void Off() override;
private:
	int val;
	static int gh;
};

#endif
