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
#include"changedirectioncomponent.h"
#include<algorithm>
#include"inventorycomponent.h"

Player::Player(GameStage* game, vector<vector<RogueLikeMap>>& map) :Actor(game), mapdata(map){
	if (-1 == LoadDivGraph("Images\\Chicken_black.png", 24, 6, 4, 32, 32, gh)) MSG("プレイヤー画像読み込みエラー");
	SpriteComponent* sc = new CharacterSprite(this, 100);
	sc->SetImage(gh);
	if (damageeffect[0] == 0) LoadDivGraph("Images\\damageeffect.png", 2, 2, 1, 32, 32, damageeffect);
	DamageEffect* de = new DamageEffect(this, 150);
	de->SetImage(damageeffect);

	PlayerMoveComponent* pmc = new PlayerMoveComponent(this);
	PlayerAttackComponent* pac = new PlayerAttackComponent(this);
	ChangeDirectionComponent* cdc = new ChangeDirectionComponent(this);
	InventoryComponent* ic = new InventoryComponent(this);

	SetPosition(Vector2(320, 224));
	dir = DOWN;
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
	param.maxhp = 15;
	param.nowhp = 15;
	//仮
	param.name = "にわとり";
	dirbox = GetGameStage()->GetMapData()->GetDirBox();
	actcount = 0;
	mcount = 0;
}

Player::~Player() {

}

void Player::updateActor() {
	mcount++;
	//ダメージ = 攻撃力 - 防御力
	if (damageAmount) {
		if (damageAmount > param.defense) param.nowhp -= (damageAmount - param.defense);
		else param.nowhp -= 1;
	}
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
	if (param.nowhp <= 0) {
		SetState(DEAD);
		GetGameStage()->SetGameOverFlag(true);
		GameStage::ri.experience = param.experience;
		GameStage::ri.chickNum = chickNum;
		GameStage::ri.hp = param.maxhp;
		GameStage::ri.level = param.level;
		GameStage::ri.plname = param.name;
	}
}

void Player::ActorInput(InputManager* input) {
	if (as == KEY_INPUT) {
		if (input->isPushX(0)) {
			switch (dir) {
			case UP: *dirbox = 0; break;
			case DOWN: *dirbox = 1; break;
			case RIGHT: *dirbox = 2; break;
			case LEFT: *dirbox = 3; break;
			case UP_RIGHT: *dirbox = 4; break;
			case DOWN_RIGHT: *dirbox = 5; break;
			case UP_LEFT: *dirbox = 6; break;
			case DOWN_LEFT: *dirbox = 7; break;
			default: *dirbox = -1; break;
			}
		}
		else if (input->isPushRight(0) && mcount % 5 == 0) {
			if (input->isPushUp(0) && mcount % 5 == 0)dir = UP_RIGHT;
			else if (input->isPushDown(0) && mcount % 5 == 0) dir = DOWN_RIGHT;
			else dir = RIGHT;
			as = MOVE_BEGIN;
			actcount++;
		}
		else if (input->isPushLeft(0) && mcount % 5 == 0) {
			if (input->isPushUp(0) && mcount % 5 == 0) dir = UP_LEFT;
			else if (input->isPushDown(0) && mcount % 5 == 0) dir = DOWN_LEFT;
			else dir = LEFT;
			as = MOVE_BEGIN;
			actcount++;
		}
		else if (input->isPushUp(0) && mcount % 5 == 0) {
			if (input->isPushRight(0) && mcount % 5 == 0) dir = UP_RIGHT;
			else if (input->isPushLeft(0) && mcount % 5 == 0) dir = UP_LEFT;
			else dir = UP;
			as = MOVE_BEGIN;
			actcount++;
		}
		else if (input->isPushDown(0) && mcount % 5 == 0) {
			if (input->isPushRight(0) && mcount % 5 == 0) dir = DOWN_RIGHT;
			else if (input->isPushLeft(0) && mcount % 5 == 0) dir = DOWN_LEFT;
			else dir = DOWN;
			as = MOVE_BEGIN;
			actcount++;
		}
		if (input->isPushA(0)) {
			if (input->isPushRight(0)) {
				if (input->isPushUp(0))dir = UP_RIGHT;
				else if (input->isPushDown(0)) dir = DOWN_RIGHT;
				else dir = RIGHT;
				as = MOVE_BEGIN;
				actcount++;
			}
			else if (input->isPushLeft(0)) {
				if (input->isPushUp(0)) dir = UP_LEFT;
				else if (input->isPushDown(0)) dir = DOWN_LEFT;
				else dir = LEFT;
				as = MOVE_BEGIN;
				actcount++;
			}
			else if (input->isPushUp(0)) {
				if (input->isPushRight(0)) dir = UP_RIGHT;
				else if (input->isPushLeft(0)) dir = UP_LEFT;
				else dir = UP;
				as = MOVE_BEGIN;
				actcount++;
			}
			else if (input->isPushDown(0)) {
				if (input->isPushRight(0)) dir = DOWN_RIGHT;
				else if (input->isPushLeft(0)) dir = DOWN_LEFT;
				else dir = DOWN;
				as = MOVE_BEGIN;
				actcount++;
			}
		}
		if (input->isPushB()) { as = ACT_BEGIN; actcount++; }
		if (input->isPushY(0)) as = ITEM_MENU;
	}
	if (actcount != 0 && actcount % 500 == 0) enemyaddflag = true;
}

bool Player::RightWall() {
	int px = scrollx / CHIPSIZE;
	int py = scrolly / CHIPSIZE;
	for (auto enemy : *GetGameStage()->GetEnemies()) {
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
	for (auto enemy : *GetGameStage()->GetEnemies()) {
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
	for (auto enemy : *GetGameStage()->GetEnemies()) {
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
	for (auto enemy : *GetGameStage()->GetEnemies()) {
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
	for (auto enemy : *GetGameStage()->GetEnemies()) {
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
	for (auto enemy : *GetGameStage()->GetEnemies()) {
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
	for (auto enemy : *GetGameStage()->GetEnemies()) {
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
	for (auto enemy : *GetGameStage()->GetEnemies()) {
		int ex = enemy->GetIndexX();
		int ey = enemy->GetIndexY();
		if (px - 1 == ex && py + 1 == ey) return true;
	}
	if (mapdata[py + 1][px - 1].mapData == 1) return true;
	return false;
}

void Player::SetPlayerParam(PlayerParameter& param) {
	this->param.attack += param.attack;
	this->param.defense += param.defense;
	this->param.experience += param.experience;
	this->param.level += param.level;
	this->param.maxhp += param.maxhp;
	this->param.nowhp += param.nowhp;
}

int Player::chickNum;
int Player::damageeffect[2];