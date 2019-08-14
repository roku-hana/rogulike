#include "movecomponent.h"
#include "actor.h"
#include"gamestage.h"
#include"player.h"
#include"animdraw.h"

const int DRAW_PLAYER_X = 320;
const int DRAW_PLAYER_Y = 224;

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	moveX = 0;
	moveY = 0;
}

void MoveComponent::update()
{
	if (mOwner->GetMoveFlag())
	{
		switch (mOwner->GetDirection()) {
		case UP: moveY =  DRAW_PLAYER_Y + 32; moveX = DRAW_PLAYER_X + 5; break;
		case DOWN: moveY = DRAW_PLAYER_Y - 32 + 10; moveX = DRAW_PLAYER_X + 5; break;
		case LEFT: moveY = DRAW_PLAYER_Y + 5; moveX = DRAW_PLAYER_X + 32; break;
		case RIGHT: moveY = DRAW_PLAYER_Y + 5; moveX = DRAW_PLAYER_X - 32; break;
		case UP_LEFT: moveY = DRAW_PLAYER_Y + 32; moveX = DRAW_PLAYER_X + 32; break;
		case UP_RIGHT: moveY = DRAW_PLAYER_Y + 32; moveX = DRAW_PLAYER_X - 32; break;
		case DOWN_RIGHT: moveY = DRAW_PLAYER_Y - 32; moveX = DRAW_PLAYER_X - 32; break;
		case DOWN_LEFT: moveY = DRAW_PLAYER_Y - 32; moveX = DRAW_PLAYER_X + 32; break;
		default: break;
		}
		Vector2 pos = mOwner->GetPosition();
		Vector2 add = Vector2(moveX, moveY);
		pos = add;

		mOwner->SetPosition(pos);
	}
}
