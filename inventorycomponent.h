#ifndef __INVENTORYCOMPONENT_H__
#define __INVENTORYCOMPONENT_H__

#include"component.h"
#include<vector>
using namespace std;

class Player;
class Item;

enum ITEM_MENU_KND {
	BELONGINGS,
	BELONGINGS_USE,
	OTHERS,
	I_NONE
};

enum ITEM_SUBMENU_KND {
	USE,
	EXPLANATION,
	PUT,
	THROW,
	IS_NONE,
};

struct Cursole {
	int x, y;
	int pos;
	int r;
};

class InventoryComponent : public Component {
public:
	InventoryComponent(class Actor* owner, int updateOrder = 10);
	void update() override;
	void ProcessInput(InputManager* input) override;
	vector<Item*>& GetItems() { return items; }
	ITEM_MENU_KND GetItemMenuKnd() { return imk; }
	ITEM_SUBMENU_KND GetItemSubMenuKnd() { return imk2; }
	Cursole& GetCursole(){ return cursole; }
	Cursole& GetCursole2() { return cursole2; }
private:
	Player* player;
	vector<Item*> items;
	ITEM_MENU_KND imk;
	ITEM_SUBMENU_KND imk2;
	bool flag;
	Cursole cursole;
	Cursole cursole2;
	void Belongings();
	void Others();
	void ResetCursole();
	void ResetCursole2();
};

#endif
