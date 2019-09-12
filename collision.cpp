#include"collision.h"
#include"player.h"
#include"chick.h"
#include"gamestage.h"
#include"item.h"

Collision::Collision(GameStage* gs) : gs(gs)
{
}

Collision::~Collision() {}

void Collision::Player_Chick_Collision() {
	int px = *gs->GetPlayer()->GetScrollX() / 32;
	int py = *gs->GetPlayer()->GetScrollY() / 32;
	
	for (auto ck : gs->GetChicks()){
		if (px == ck->GetIndexX() && py == ck->GetIndexY()) {
			ck->SetMoveFlag(true);
		}
	}
}

void Collision::Player_Item_Collision() {
	int px = *gs->GetPlayer()->GetScrollX() / 32;
	int py = *gs->GetPlayer()->GetScrollY() / 32;

	for (auto it : gs->GetItems()) {
		if (px == it->GetPosX() && py == it->GetPosY()) {
			if(!it->GetDamageFlag()) it->SetMoveFlag(true);
		}
	}
}