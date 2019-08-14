#include "movecomponent.h"
#include "actor.h"
#include"gamestage.h"
#include"player.h"
#include"animdraw.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{

}

void MoveComponent::update()
{
	if (isMove())
	{
		int px = *mOwner->GetGameStage()->GetPlayer()->GetScrollX();
		int py = *mOwner->GetGameStage()->GetPlayer()->GetScrollY();

		switch (mOwner->GetDirection()) {
		case UP: moveY = py + 1; moveX = px; break;
		case DOWN: moveY = py - 1; moveX = px; break;
		case LEFT: moveY = py; moveX = px + 1; break;
		case RIGHT: moveY = py; moveX = px - 1; break;
		case UP_LEFT: moveY = py + 1; moveX = px + 1; break;
		case UP_RIGHT: moveY = py + 1; moveY = px - 1; break;
		case DOWN_RIGHT: moveY = py - 1; moveX = px - 1; break;
		case DOWN_LEFT: moveY = py - 1; moveX = px + 1; break;
		default: break;
		}
		Vector2 pos = mOwner->GetPosition();
		Vector2 add = Vector2(moveX * AMOUNT_OF_MOVEMENT, moveY * AMOUNT_OF_MOVEMENT);
		pos += add;


		mOwner->SetPosition(pos);
	}
}

bool MoveComponent::isMove() {
	if (moveX == 1 || moveY == 1) return true;
	return false;
}
