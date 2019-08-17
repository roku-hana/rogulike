#include"playermovecomponent.h"
#include"player.h"
#include"animdraw.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	player = (Player*)owner;
	px = player->GetScrollX();
	py = player->GetScrollY();
}

void PlayerMoveComponent::update() {
	if (player->GetMoveFlag()) {
		if (player->CanMove()) {
			switch (player->GetDirection()) {
			case UP: if (!player->UpWall()) (*py) -= CHIPSIZE; break;
			case DOWN: if (!player->DownWall()) (*py) += CHIPSIZE; break;
			case RIGHT: if (!player->RightWall()) (*px) += CHIPSIZE; break;
			case LEFT: if (!player->LeftWall()) (*px) -= CHIPSIZE; break;
			case UP_RIGHT: if (!player->Up_Right_Wall()) { (*px) += CHIPSIZE; (*py) -= CHIPSIZE; } break;
			case UP_LEFT: if (!player->Up_Left_Wall()) { (*px) -= CHIPSIZE; (*py) -= CHIPSIZE; } break;
			case DOWN_RIGHT: if (!player->Down_Right_Wall()){ (*px) += CHIPSIZE; (*py) += CHIPSIZE; } break;
			case DOWN_LEFT: if (!player->Down_Left_Wall()) { (*px) -= CHIPSIZE; (*py) += CHIPSIZE; } break;
			default: break;
			}
		}
	}
}