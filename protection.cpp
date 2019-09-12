#include"protection.h"
#include<DxLib.h>
#include"spritecomponent.h"
#include"gamestage.h"
#include"player.h"

Protection::Protection(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, ItemData* temp) :
	Item(game, map, x, y) 
{
	if (gh == 0) gh = LoadGraph("Images\\item\\ƒAƒCƒRƒ“\\icon010.png");

	SpriteComponent* sc = new SpriteComponent(this, 50);
	sc->SetImage(&gh);

	name = temp->name;
	id = temp->id;
	category = temp->category;
	val = temp->val;
	explanation = temp->explanation;
	equip = false;
}

Protection::~Protection() {

}

void Protection::Use() {
	PlayerParameter temp = {};
	temp.defense = val;
	GetGameStage()->GetPlayer()->SetPlayerParam(temp);
	equip = true;
}

void Protection::Off() {
	PlayerParameter temp = {};
	temp.defense -= val;
	GetGameStage()->GetPlayer()->SetPlayerParam(temp);
	equip = false;
}

int Protection::gh;