#ifndef __RECOVERY_H__
#define __RECOVERY_H__

#include"item.h"

class Recovery : public Item {
public:
	Recovery(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, ItemData* temp);
	~Recovery();
	void Use() override;
private:
	int val;
	static int gh;
};

#endif
