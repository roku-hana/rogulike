#ifndef __ITEMINVENTORYSPRITE_H__
#define __ITEMINVENTORYSPRITE_H__

#include"spritecomponent.h"
#include"actor.h"
#include<vector>
using namespace std;

class Item;
class InventoryComponent;
class Player;

class ItemInventorySprite : public SpriteComponent {
public:
	ItemInventorySprite(Actor* owner, int drawOrder, InventoryComponent* ic);
	~ItemInventorySprite() {};
	void Draw(int count) override;
private:
	int smallfont;
	InventoryComponent* ic;
	Player* player;
	void DrawMenu();
	void DrawBelongings();
	void DrawBelongingsUse();
	void DrawExplanation();
	void DrawOthers();
	int weapon;
	int protection;
	int recovery;
};

#endif
