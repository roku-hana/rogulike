#include"playerattackcomponent.h"
#include"player.h"
#include"gamestage.h"
#include"enemy.h"
#include"animdraw.h"
#include<DxLib.h>
#include"soundbox.h"

PlayerAttackComponent::PlayerAttackComponent(class Actor* owner, int updateOrder) 
	:Component(owner, updateOrder)
{
	player = (Player*)owner;
	enemies = player->GetGameStage()->GetEnemies();
	timerstart = 0;
	enemyKnd = -1;
	count = 0;
}

void PlayerAttackComponent::update() {
	if (player->GetActState() == ACT_BEGIN) {
		if (timerstart == 0) {
			Attack();
			SoundBox::playSound(2);
		}
		if (enemies->size() > 0) player->SetActState(ACT_END);
		else player->SetActState(KEY_INPUT);
		if (enemyKnd == -1) {
			if (timerstart == 0) timerstart = GetNowCount();
		}
	}
	if(enemyKnd != -1) {
		Message();
		if (timerstart == 0) { timerstart = GetNowCount(); player->GetGameStage()->SetMessageFlag(true);}
		if (GetNowCount() - timerstart >= 1000) {
			for (auto enemy : *enemies) { enemy->SetActState(WAIT); }
			timerstart = 0;
			enemyKnd = -1;
			count = 0;
			player->GetGameStage()->SetMessageFlag(false);
			player->SetMoveFlag(true);
		}
		if (GetNowCount() - timerstart <= 500) Animation();
		else for (auto enemy : *enemies) enemy->SetDamageFlag(false);
	}
	else if(timerstart != 0){
		if (GetNowCount() - timerstart <= 500) { Animation(); player->SetActState(ANIMATION); }
		if (GetNowCount() - timerstart >= 1000) {
			for (auto enemy : *enemies) { enemy->SetActState(WAIT); }
			timerstart = 0;
			count = 0;
			player->SetMoveFlag(true);
		}
	}
}

void PlayerAttackComponent::Attack() {
	int px = *player->GetScrollX() / 32;
	int py = *player->GetScrollY() / 32;
	int pa = player->GetPlayerParam().attack;
	for (int i = 0; i < (*enemies).size(); i++) {
		int ex = (*enemies)[i]->GetIndexX();
		int ey = (*enemies)[i]->GetIndexY();
		switch (player->GetDirection()) {
		case UP: if (px == ex && py - 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		case DOWN: if (px == ex && py + 1 == ey) { (*enemies)[i]->SetDamageAmount(pa);  enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		case RIGHT: if (px + 1 == ex && py == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		case LEFT: if (px - 1 == ex && py == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		case UP_RIGHT: if (px + 1 == ex && py - 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		case UP_LEFT: if (px - 1 == ex && py - 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		case DOWN_RIGHT: if (px + 1 == ex && py + 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		case DOWN_LEFT: if (px - 1 == ex && py + 1 == ey) { (*enemies)[i]->SetDamageAmount(pa); enemyKnd = i; (*enemies)[i]->SetDamageFlag(true); } break;
		default: break;
		}
	}
}

void PlayerAttackComponent::Message() {
	if (enemies->size() > 0) {
		int id = (*enemies)[enemyKnd]->GetEnemyParam().id;
		string pl = player->GetPlayerParam().name;;
		string en = (*enemies)[enemyKnd]->GetEnemyName(id);
		int val = player->GetPlayerParam().attack - (*enemies)[enemyKnd]->GetEnemyParam().defense;
		if (timerstart == 0) player->GetGameStage()->SetMessage(0, pl, en, val);
	}
	else player->SetActState(KEY_INPUT);
}

void PlayerAttackComponent::Animation() {
	count++;
	Vector2 add;
	switch (player->GetDirection()) {
	case UP:  add.y -= (float)sin(3.14 * 2 / 30 * count) * 2; break;
	case DOWN: add.y += (float)sin(3.14 * 2 / 30 * count) * 2; break;
	case RIGHT: add.x += (float)sin(3.14 * 2 / 30 * count) * 2; break;
	case LEFT: add.x -= (float)sin(3.14 * 2 / 30 * count) * 2; break;
	case UP_RIGHT: add.x += (float)sin(3.14 * 2 / 30 * count) * 2; add.y -= (float)sin(3.14 * 2 / 30 * count) * 2; break;
	case UP_LEFT: add.x -= (float)sin(3.14 * 2 / 30 * count) * 2; add.y -= (float)sin(3.14 * 2 / 30 * count) * 2; break;
	case DOWN_RIGHT: add.x += (float)sin(3.14 * 2 / 30 * count) * 2; add.y += (float)sin(3.14 * 2 / 30 * count) * 2; break;
	case DOWN_LEFT: add.x -= (float)sin(3.14 * 2 / 30 * count) * 2; add.y += (float) sin(3.14 * 2 / 30 * count) * 2; break;
	default: break;
	}
	player->SetPosition(Vector2(player->GetPosition().x + add.x, player->GetPosition().y + add.y));
}