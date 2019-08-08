#include "movecomponent.h"
#include "actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{

}

void MoveComponent::update()
{
	if (isMove())
	{
		Vector2 pos = mOwner->GetPosition();
		Vector2 add = Vector2(moveX * AMOUNT_OF_MOVEMENT, moveY * AMOUNT_OF_MOVEMENT);
		pos += add;

		/*if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }*/

		mOwner->SetPosition(pos);
	}
}

bool MoveComponent::isMove() {
	if (moveX == 1 || moveY == 1) return true;
	return false;
}
