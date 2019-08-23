#include"enemyattackcomponent.h"
#include"player.h"
#include"gamestage.h"
#include"enemy.h"
#include"animdraw.h"
#include<DxLib.h>

EnemyAttackComponent::EnemyAttackComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	player = owner->GetGameStage()->GetPlayer();
	enemy = (Enemy*)owner;
	timerstart = 0;
	messageflag = false;
}

void EnemyAttackComponent::update() {
	if (enemy->GetActState() == ACT_BEGIN) {
		if (timerstart == 0) Attack();
		enemy->SetActState(ACT_END);
	}
	if (messageflag) Message();
}

void EnemyAttackComponent::Attack() {
	int ea = enemy->GetEnemyParam().attack;

	player->SetDamageAmount(ea);
	messageflag = true;
}

void EnemyAttackComponent::Message() {
	int id = enemy->GetEnemyParam().id;
	string pl = player->GetPlayerParam().name;;
	string en = enemy->GetEnemyName(id);
	if (timerstart == 0) { 
		timerstart = GetNowCount(); 
		player->GetGameStage()->SetMessage(1, pl, en, enemy->GetEnemyParam().attack);
		player->GetGameStage()->SetMessageFlag(true);
	}
	if(GetNowCount() - timerstart >= 1000){
		timerstart = 0;
		player->SetActState(KEY_INPUT);
		player->GetGameStage()->SetMessageFlag(false);
		messageflag = false;
	}
}