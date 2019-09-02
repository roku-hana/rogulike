#include"enemymovecomponent.h"
#include"player.h"
#include"gamestage.h"
#include"actor.h"
#include"animdraw.h"
#include"enemy.h"

EnemyMoveComponent::EnemyMoveComponent(Actor* owner, int*ex, int* ey, int updateOrder)
	:Component(owner, updateOrder),
	ex(ex), ey(ey)
{
	player = owner->GetGameStage()->GetPlayer();
	enemy = (Enemy*)mOwner;
}

void EnemyMoveComponent::update() {
	if (enemy->GetActState() == MOVE_BEGIN) {
		enemy->SetActState(MOVE_END);
		move();
	}
}

void EnemyMoveComponent::move() {
	if (mOwner->GetMoveFlag()) {
		switch (mOwner->GetDirection()) {
		case UP: (*ey) -= 1; break;
		case UP_RIGHT: (*ey) -= 1; (*ex) += 1; break;
		case UP_LEFT: (*ey) -= 1; (*ex) -= 1; break;
		case DOWN: (*ey) += 1; break;
		case DOWN_RIGHT: (*ey) += 1; (*ex) += 1; break;
		case DOWN_LEFT: (*ey) += 1; (*ex) -= 1; break;
		case RIGHT: (*ex) += 1; break;
		case LEFT: (*ex) -= 1; break;
		default: break;
		}
	}
}