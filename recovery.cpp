#include"recovery.h"
#include<DxLib.h>
#include"spritecomponent.h"
#include"gamestage.h"
#include"player.h"

Recovery::Recovery(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, ItemData* temp) :
Item(game, map, x, y)
{
	if (gh == 0) gh = LoadGraph("Images\\item\\ƒAƒCƒRƒ“\\icon030.png");

	SpriteComponent* sc = new SpriteComponent(this, 50);
	sc->SetImage(&gh);

	name = temp->name;
	id = temp->id;
	category = temp->category;
	val = temp->val;
	explanation = temp->explanation;
}

Recovery::~Recovery() {

}

void Recovery::Use() {
	PlayerParameter temp = {};
	temp.nowhp = val;
	GetGameStage()->GetPlayer()->SetPlayerParam(temp);
}

int Recovery::gh;