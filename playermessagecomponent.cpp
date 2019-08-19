#include"playermessagecomponent.h"
#include"player.h"
#include"gamestage.h"
#include"enemy.h"

PlayerMessageComponent::PlayerMessageComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder) {
	player = (Player*)owner;
	enemies = player->GetGameStage()->GetEnemies();
}

void PlayerMessageComponent::update() {

}

void PlayerMessageComponent::Message() {

}