#include"gamestage.h"
//#include"makedungeon.h"
#include"spritecomponent.h"
#include"player.h"
#include"stagetest.h"

GameStage::GameStage(InputManager* temp):input(temp) {
	//mp = new MapData();
	player = new Player(this);
	stage = new StageTest();
}

GameStage::~GameStage() {
	//delete mp;
	delete player;
	delete stage;
}

void GameStage::update() {
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
}

void GameStage::draw() {
	//mp->draw();
	//‰¼
	stage->draw(player->GetScrollX(), player->GetScrollY());

	for (auto sprite : mSprites)
	{
		sprite->Draw();
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
	// (We can't swap because it ruins ordering)
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
