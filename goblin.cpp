#include"goblin.h"
#include<DxLib.h>
#include"error.h"
#include"charactersprite.h"
#include"enemymovecomponent.h"
#include"enemyattackcomponent.h"
#include"gamestage.h"

Goblin::Goblin(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y, int* px, int* py, EnemyParameter ep) :
	Enemy(game, map, x, y, px, py)
{
	if (gh[0] == 0) {
		if (-1 == LoadDivGraph("Images\\Goblin1_green.png", 24, 6, 4, 32, 32, gh)) MSG("イノシシ画像読み込みエラー");
	}

	SpriteComponent* sc = new CharacterSprite(this, 50);
	sc->SetImage(gh);

	EnemyMoveComponent* emc = new EnemyMoveComponent(this, &indexX, &indexY);
	EnemyAttackComponent* eac = new EnemyAttackComponent(this, &indexX, &indexY);

	param = ep;
	SetPosition(Vector2(-10, -10));
	dir = DOWN;
	temp = NONE;
	as = WAIT;
}

Goblin::~Goblin() {

}

void Goblin::updateActor() {
	Enemy::updateActor();
}

void Goblin::ActorInput(InputManager* input) {

}

int Goblin::gh[24];