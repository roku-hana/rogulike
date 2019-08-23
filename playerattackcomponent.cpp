#include"playerattackcomponent.h"
#include"player.h"
#include"gamestage.h"
#include"enemy.h"
#include"animdraw.h"
#include<DxLib.h>

PlayerAttackComponent::PlayerAttackComponent(class Actor* owner, int updateOrder) 
	:Component(owner, updateOrder)
{
	player = (Player*)owner;
	enemies = player->GetGameStage()->GetEnemies();
	timerstart = 0;
	enemyKnd = -1;
}

void PlayerAttackComponent::update() {
	if (player->GetActState() == ACT_BEGIN) {
		if (timerstart == 0) Attack();
		player->SetActState(ACT_END);
		if (enemyKnd == -1) {
			for (auto enemy : *enemies) enemy->SetActState(WAIT);
		}
	}
	if (enemyKnd != -1) Message();
}

void PlayerAttackComponent::Attack() {
	int px = *player->GetScrollX() / 32;
	int py = *player->GetScrollY() / 32;
	int pa = player->GetPlayerParam().attack;
	for (int i = 0; i < (*enemies).size(); i++) {
		int ex = (*enemies)[i]->GetIndexX();
		int ey = (*enemies)[i]->GetIndexY();
		switch (player->GetDirection()) {
		case UP: if (px == ex && py - 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; } break;
		case DOWN: if (px == ex && py + 1 == ey) { (*enemies)[i]->SetDamageAmount(pa);  enemyKnd = i; } break;
		case RIGHT: if (px + 1 == ex && py == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; } break;
		case LEFT: if (px - 1 == ex && py == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; } break;
		case UP_RIGHT: if (px + 1 == ex && py - 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; } break;
		case UP_LEFT: if (px - 1 == ex && py - 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; } break;
		case DOWN_RIGHT: if (px + 1 == ex && py + 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; } break;
		case DOWN_LEFT: if (px - 1 == ex && py + 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; } break;
		default: break;
		}
	}
}

void PlayerAttackComponent::Message() {
	int id = (*enemies)[enemyKnd]->GetEnemyParam().id;
	string pl = player->GetPlayerParam().name;;
	string en = (*enemies)[enemyKnd]->GetEnemyName(id);
	if (timerstart == 0) { 
	timerstart = GetNowCount(); 
	player->GetGameStage()->SetMessage(0, pl, en, player->GetPlayerParam().attack); 
	player->GetGameStage()->SetMessageFlag(true);
	}
	if(GetNowCount() - timerstart >= 1000){
		for (auto enemy : *enemies) enemy->SetActState(WAIT);
		timerstart = 0;
		enemyKnd = -1;
		player->GetGameStage()->SetMessageFlag(false);
	}
}