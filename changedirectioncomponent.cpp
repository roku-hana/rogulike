#include"changedirectioncomponent.h"
#include"player.h"
#include"input.h"
#include"gamestage.h"
#include"animdraw.h"

ChangeDirectionComponent::ChangeDirectionComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	player = (Player*)owner;
}

void ChangeDirectionComponent::update() {
	
}

void ChangeDirectionComponent::ProcessInput(InputManager* input) {
	if (player->GetDirBox() != -1) {
		if (input->isPushRight(0)) {
			if (input->isPushUp(0))player->SetDirection(UP_RIGHT);
			else if (input->isPushDown(0)) player->SetDirection(DOWN_RIGHT);
			else player->SetDirection(RIGHT);
		}
		else if (input->isPushLeft(0)) {
			if (input->isPushUp(0)) player->SetDirection(UP_LEFT);
			else if (input->isPushDown(0)) player->SetDirection(DOWN_LEFT);
			else player->SetDirection(LEFT);
		}
		else if (input->isPushUp(0)) {
			if (input->isPushRight(0)) player->SetDirection(UP_RIGHT);
			else if (input->isPushLeft(0)) player->SetDirection(UP_LEFT);
			else player->SetDirection(UP);
		}
		else if (input->isPushDown(0)) {
			if (input->isPushRight(0)) player->SetDirection(DOWN_RIGHT);
			else if (input->isPushLeft(0)) player->SetDirection(DOWN_LEFT);
			else player->SetDirection(DOWN);
		}
	}
}