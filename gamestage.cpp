#include"gamestage.h"
#include"makedungeon.h"
#include"spritecomponent.h"
#include"player.h"
#include"chick.h"
#include"collision.h"

GameStage::GameStage(InputManager* temp):input(temp) {
	mp = new MapData();
	player = new Player(this, mp->GetMap());
	player->SetScrollX(mp->GetStartX() * CHIPSIZE);
	player->SetScrollY(mp->GetStartY() * CHIPSIZE);
	for (int i = 0; i < mp->GetChickNum(); i++) {
		new Chick(this, mp->GetChickX(i), mp->GetChickY(i), player->GetScrollX(), player->GetScrollY());
	}
	nextStage = 0;
	colManager = new Collision(this);
}

GameStage::~GameStage() {
	delete player;
	delete mp;
	delete colManager;
}

void GameStage::update() {
	animcounter++;
	if (*player->GetScrollX() / CHIPSIZE == mp->GetGoalX() && *player->GetScrollY() / CHIPSIZE == mp->GetGoalY()) nextStage = mp->GetStageNum() + 1;
	else nextStage = 0;

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->update();
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::DEAD)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

	colManager->Player_Chick_Collision();
}

void GameStage::draw() {
	mp->draw(*player->GetScrollX(), *player->GetScrollY());
	mp->DrawTransparentMaze(*player->GetScrollX() / CHIPSIZE, *player->GetScrollY() / CHIPSIZE);
	//mp->DrawTempMap();

	for (auto sprite : mSprites)
	{
		sprite->Draw(animcounter, player->GetDirection());
	}
}

void GameStage::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void GameStage::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void GameStage::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void GameStage::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void GameStage::ProcessInput() {
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(input);
	}
	mUpdatingActors = false;
}

void GameStage::AddChick(Chick* chick) {
	mChicks.emplace_back(chick);
}

void GameStage::RemoveChick(Chick* chick) {
	auto iter = std::find(mChicks.begin(),
		mChicks.end(), chick);
	if (iter != mChicks.end())
	{
		mChicks.erase(iter);
	}
}