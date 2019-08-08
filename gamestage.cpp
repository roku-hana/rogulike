#include"gamestage.h"
#include"makedungeon.h"

GameStage::GameStage() {
	mp = new MapData();
}

GameStage::~GameStage() {
	delete mp;
}

void GameStage::update() {

}

void GameStage::draw() {
	mp->draw();
}

void GameStage::AddActor(Actor* actor)
{
	/*if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}*/
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