#include"playermovecomponent.h"
#include"player.h"
#include"animdraw.h"
#include"gamestage.h"
#include"enemy.h"
#include<DxLib.h>

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	player = (Player*)owner;
	enemies = player->GetGameStage()->GetEnemies();
	px = player->GetScrollX();
	py = player->GetScrollY();
}

void PlayerMoveComponent::update() {
	if (player->GetActState() == MOVE_BEGIN) {
		Move();
		if (enemies->size() > 0) player->SetActState(MOVE_END);
		else player->SetActState(KEY_INPUT);
		for (auto enemy : *enemies) enemy->SetActState(WAIT);
	}
}

void PlayerMoveComponent::Move() {
	switch (player->GetDirection()) {
	case UP: if (!player->UpWall()) { (*py) -= CHIPSIZE; player->SetMoveFlag(true); }
			 else player->SetMoveFlag(false); break;
	case DOWN: if (!player->DownWall()) { (*py) += CHIPSIZE; player->SetMoveFlag(true); }
			   else player->SetMoveFlag(false); break;
	case RIGHT: if (!player->RightWall()) { (*px) += CHIPSIZE; player->SetMoveFlag(true); }
				else player->SetMoveFlag(false); break;
	case LEFT: if (!player->LeftWall()) { (*px) -= CHIPSIZE; player->SetMoveFlag(true); }
			   else player->SetMoveFlag(false); break;
	case UP_RIGHT: if (!player->Up_Right_Wall()) { (*px) += CHIPSIZE; (*py) -= CHIPSIZE; player->SetMoveFlag(true); }
				   else player->SetMoveFlag(false); break;
	case UP_LEFT: if (!player->Up_Left_Wall()) { (*px) -= CHIPSIZE; (*py) -= CHIPSIZE; player->SetMoveFlag(true); }
				  else player->SetMoveFlag(false); break;
	case DOWN_RIGHT: if (!player->Down_Right_Wall()) { (*px) += CHIPSIZE; (*py) += CHIPSIZE; player->SetMoveFlag(true); }
					 else player->SetMoveFlag(false); break;
	case DOWN_LEFT: if (!player->Down_Left_Wall()) { (*px) -= CHIPSIZE; (*py) += CHIPSIZE; player->SetMoveFlag(true); }
					else player->SetMoveFlag(false); break;
	default: break;
	}
}