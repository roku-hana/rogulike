#include"enemyattackcomponent.h"
#include"player.h"
#include"gamestage.h"
#include"enemy.h"
#include"animdraw.h"
#include<DxLib.h>
#include"soundbox.h"

EnemyAttackComponent::EnemyAttackComponent(class Actor* owner, int*x, int* y, int updateOrder)
	:Component(owner, updateOrder), ex(x), ey(y)
{
	player = owner->GetGameStage()->GetPlayer();
	enemy = (Enemy*)owner;
	timerstart = 0;
	count = 0;
	messageflag = false;
}

void EnemyAttackComponent::update() {
	if (enemy->GetActState() == ACT_BEGIN) {
		if (timerstart == 0) { Attack();}
		enemy->SetActState(ACT_END);
	}
	if (messageflag) Message();
}

void EnemyAttackComponent::Attack() {
	int ea = enemy->GetEnemyParam().attack;

	player->SetDamageAmount(ea);
	player->SetDamageFlag(true);
	messageflag = true;
}

void EnemyAttackComponent::Message() {
	int id = enemy->GetEnemyParam().id;
	string pl = player->GetPlayerParam().name;;
	string en = enemy->GetEnemyName(id);
	int val = enemy->GetEnemyParam().attack - player->GetPlayerParam().defense;
	if(timerstart == 0) player->GetGameStage()->SetMessage(1, pl, en, val);
	if (timerstart == 0) { 
		SoundBox::playSound(3);
		timerstart = GetNowCount(); 
		player->GetGameStage()->SetMessageFlag(true);
	}
	if (GetNowCount() - timerstart >= 1000) {
		timerstart = 0;
		count = 0;
		player->SetActState(KEY_INPUT);
		player->GetGameStage()->SetMessageFlag(false);
		messageflag = false;
	}
	if (GetNowCount() - timerstart <= 500) Animation();
	//else player->SetDamageFlag(false);
}

void EnemyAttackComponent::Animation() {
	count++;
	Vector2 add;
	switch (enemy->GetDirection()) {
	case UP:  add.y -= (float)sin(3.14 * 2 / 30 * count) * 4; break;
	case DOWN: add.y += (float)sin(3.14 * 2 / 30 * count) * 4; break;
	case RIGHT: add.x += (float)sin(3.14 * 2 / 30 * count) * 4; break;
	case LEFT: add.x -= (float)sin(3.14 * 2 / 30 * count) * 4; break;
	case UP_RIGHT: add.x += (float)sin(3.14 * 2 / 30 * count) * 4; add.y -= (float)sin(3.14 * 2 / 30 * count) * 4; break;
	case UP_LEFT: add.x -= (float)sin(3.14 * 2 / 30 * count) * 4; add.y -= (float)sin(3.14 * 2 / 30 * count) * 4; break;
	case DOWN_RIGHT: add.x += (float)sin(3.14 * 2 / 30 * count) * 4; add.y += (float)sin(3.14 * 2 / 30 * count) * 4; break;
	case DOWN_LEFT: add.x -= (float)sin(3.14 * 2 / 30 * count) * 4; add.y += (float)sin(3.14 * 2 / 30 * count) * 4; break;
	default: break;
	}
	enemy->SetPosition(Vector2(enemy->GetPosition().x + add.x, enemy->GetPosition().y + add.y));
}