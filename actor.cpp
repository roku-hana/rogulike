#include "actor.h"
#include "gamestage.h"
#include "component.h"
#include <algorithm>
#include"input.h"

Actor::Actor(GameStage* gamestage)
	:mState(ACTIVE)
	, mPosition(Vector2::Zero)
	, mGameStage(gamestage)
{
	mGameStage->AddActor(this);
}

Actor::~Actor()
{
	mGameStage->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::update()
{
	if (mState == ACTIVE)
	{
		//updateComponents();
		updateActor();
		updateComponents();
	}
}

void Actor::updateComponents()
{
	for (auto comp : mComponents)
	{
		comp->update();
	}
}

void Actor::updateActor()
{
}

//Œã‚Åˆø”‚ð•Ï‚¦‚é
void Actor::ProcessInput(InputManager* input)
{
	if (mState == ACTIVE)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(input);
		}

		ActorInput(input);
	}
}

void Actor::ActorInput(InputManager* input)
{
}

void Actor::AddComponent(Component* component)
{
	int myOrder = component->getUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

