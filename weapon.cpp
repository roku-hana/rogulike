#include"weapon.h"
#include"spritecomponent.h"
#include<DxLib.h>
#include"gamestage.h"
#include"player.h"

Weapon::Weapon(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, ItemData* temp) :
	Item(game, map, x, y) 
{
	if (gh == 0) gh = LoadGraph("Images\\item\\ƒAƒCƒRƒ“\\icon002.png");

	SpriteComponent* sc = new SpriteComponent(this, 50);
	sc->SetImage(&gh);

	name = temp->name;
	id = temp->id;
	category = temp->category;
	val = temp->val;
	explanation = temp->explanation;
	equip = false;
}

Weapon::~Weapon() {

}

void Weapon::Use() {
	PlayerParameter temp = {};
	temp.attack = val;
	GetGameStage()->GetPlayer()->SetPlayerParam(temp);
	equip = true;
}

void Weapon::Off() {
	PlayerParameter temp = {};
	temp.attack -= val;
	GetGameStage()->GetPlayer()->SetPlayerParam(temp);
	equip = false;
}

int Weapon::gh;