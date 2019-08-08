#ifndef __ACTOR_H__
#define __ACTOR_H__

#include"vector.h"
#include<vector>

class GameStage;
class Component;

class Actor {
public:
	enum State {
		ACTIVE,
		PAUSED,
		DEAD
	};
	Actor(GameStage* gamestage);
	virtual ~Actor();
	void update();
	void updateComponents();
	virtual void updateActor();
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);
	GameStage* GetGameStage() { return mGameStage; }
	void AddComponent(Component*);
	void RemoveComponent(Component*);
private:
	State mState;
	Vector2 mPosition;
	std::vector<Component*> mComponents;
	GameStage* mGameStage;
};

#endif
