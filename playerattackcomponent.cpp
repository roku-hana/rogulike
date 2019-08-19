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
	if (messagebox == 0) messagebox = LoadGraph("Images\\messagebox.png");
	timerstart = 0;
	enemyKnd = -1;
}

void PlayerAttackComponent::update() {
	if (player->GetActState() == ACT_BEGIN) {
		if(timerstart == 0) Attack();
		player->SetActState(ACT_END);
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
	string message = player->GetGameStage()->Get_Message(0, pl, en, player->GetPlayerParam().attack);
	if (timerstart == 0) timerstart = GetNowCount();
	if (GetNowCount() - timerstart <= 5000) {
		DrawGraph(120, 390, messagebox, TRUE);
		DrawString(130, 400, message.c_str(), GetColor(255, 255, 255));
	}
	else {
		timerstart = 0;
		enemyKnd = -1;
	}
}

int PlayerAttackComponent::messagebox;