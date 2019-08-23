#include"collision.h"
#include"player.h"
#include"chick.h"
#include"gamestage.h"

Collision::Collision(GameStage* gs){
	player = gs->GetPlayer();
	chicks = gs->GetChicks();
}

Collision::~Collision() {}

void Collision::Player_Chick_Collision() {
	int px = *player->GetScrollX() / 32;
	int py = *player->GetScrollY() / 32;
	
	for (auto ck : chicks){
		if (px == ck->GetIndexX() && py == ck->GetIndexY()) {
			ck->SetMoveFlag(true);
		}
	}
}