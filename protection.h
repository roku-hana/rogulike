#ifndef __PROTECTION_H__
#define __PROTECTION_H__

#include"item.h"

class Protection : public Item {
public:
	Protection(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, ItemData* temp);
	~Protection();
	void Use() override;
	void Off() override;
private:
	int val;
	static int gh;
};

#endif
