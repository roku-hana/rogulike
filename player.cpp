#include"player.h"
#include"error.h"
#include<DxLib.h>
#include"input.h"
#include"charactersprite.h"
#include"makedungeon.h"
#include"playermovecomponent.h"
#include"playerattackcomponent.h"
#include"gamestage.h"
#include"enemy.h"
#include"damageeffect.h"
#include"soundbox.h"

Player::Player(GameStage* game, vector<vector<RogueLikeMap>>& map) :Actor(game), mapdata(map){
	if (-1 == LoadDivGraph("Images\\Chicken_black.png", 24, 6, 4, 32, 32, gh)) MSG("プレイヤー画像読み込みエラー");
	SpriteComponent* sc = new CharacterSprite(this, 100);
	sc->SetImage(gh);
	if (damageeffect[0] == 0) LoadDivGraph("Images\\damageeffect.png", 2, 2, 1, 32, 32, damageeffect);
	DamageEffect* de = new DamageEffect(this, 150);
	de->SetImage(damageeffect);

	PlayerMoveComponent* pmc = new PlayerMoveComponent(this);
	PlayerAttackComponent* pac = new PlayerAttackComponent(this);

	SetPosition(Vector2(320, 224));
	dir = DOWN;
	//count = 0; 
	moveflag = false;
	scrollx = 0;
	scrolly = 0;
	chickNum = 0;
	as = KEY_INPUT;
	//parameterの初期化
	param.attack = 10;
	param.defense = 3;
	param.experience = 0;
	param.level = 1;
	param.maxhp = 10;
	param.nowhp = 10;
	//仮
	param.name = "にわとり";
}

Player::~Player() {

}

void Player::updateActor() {
	//ダメージ = 攻撃力 - 防御力
	if (damageAmount) param.nowhp -= (damageAmount - param.defense);
	damageAmount = 0;
	if (param.experience >= param.level * 10) {
		SoundBox::playSound(4);
		param.level++;
		//ステータス上昇後で、考える。今のところは仮の計算
		param.attack += 2;
		param.defense += 2;
		param.maxhp += 5;
		//////////////////////////////////////////////////
		param.experience = 0;
	}
	DrawFormatString(400, 30, GetColor(0, 0, 255), "player hp:%d", param.nowhp);
	DrawFormatString(150, 30, GetColor(0, 0, 255), "player exp:%d", param.experience);
	DrawFormatString(50, 10, GetColor(0, 0, 255), "player lev:%d", param.level);
	if (param.nowhp <= 0) SetState(DEAD);
}

void Player::ActorInput(InputManager* input) {
	if (as == KEY_INPUT) {
		if (input->isPushRight()) {
			if (input->isPushUp())dir = UP_RIGHT;
			else if (input->isPushDown()) dir = DOWN_RIGHT;
			else dir = RIGHT;
			as = MOVE_BEGIN;
		}
		else if (input->isPushLeft()) {
			if (input->isPushUp()) dir = UP_LEFT;
			else if (input->isPushDown()) dir = DOWN_LEFT;
			else dir = LEFT;
			as = MOVE_BEGIN;
		}
		else if (input->isPushUp()) {
			if (input->isPushRight()) dir = UP_RIGHT;
			else if (input->isPushLeft()) dir = UP_LEFT;
			else dir = UP;
			as = MOVE_BEGIN;
		}
		else if (input->isPushDown()) {
			if (input->isPushRight()) dir = DOWN_RIGHT;
			else if (input->isPushLeft()) dir = DOWN_LEFT;
			else dir = DOWN;
			as = MOVE_BEGIN;
		}
		else if (input->isPushA(0)) as = MOVE_BEGIN;
		if (input->isPushB()) as = ACT_BEGIN;
		
	}
}

bool Player::RightWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX(); 
		int ey = enemy->GetIndexY();
		if (px + 1 == ex && py == ey) return true;
	}
	if (mapdata[py][px + 1].mapData == 1) return true;
	return false;
}

bool Player::LeftWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX(); 
		int ey = enemy->GetIndexY();
		if (px - 1 == ex && py == ey) return true;
	}
	if (mapdata[py][px - 1].mapData == 1) return true;
	return false;
}

bool Player::UpWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX();
		int ey = enemy->GetIndexY();
		if (px == ex && py - 1 == ey) return true;
	}
	if (mapdata[py - 1][px].mapData == 1) return true;
	return false;
}

bool Player::DownWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX();
		int ey = enemy->GetIndexY();
		if (px == ex && py + 1 == ey) return true;
	}
	if (mapdata[py + 1][px].mapData == 1) return true;
	return false;
}

bool Player::Up_Right_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX();
		int ey = enemy->GetIndexY();
		if (px + 1 == ex && py - 1 == ey) return true;
	}
	if (mapdata[py - 1][px + 1].mapData == 1) return true;
	return false;
}

bool Player::Up_Left_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX();
		int ey = enemy->GetIndexY();
		if (px - 1 == ex && py - 1 == ey) return true;
	}
	if (mapdata[py - 1][px - 1].mapData == 1) return true;
	return false;
}

bool Player::Down_Right_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX();
		int ey = enemy->GetIndexY();
		if (px + 1 == ex && py + 1 == ey) return true;
	}
	if (mapdata[py + 1][px + 1].mapData == 1) return true;
	return false;
}

bool Player::Down_Left_Wall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : mEnemies) {
		int ex = enemy->GetIndexX();
		int ey = enemy->GetIndexY();
		if (px - 1 == ex && py + 1 == ey) return true;
	}
	if (mapdata[py + 1][px - 1].mapData == 1) return true;
	return false;
}

int Player::chickNum;
int Player::damageeffect[2];