#ifndef __ACTOR_H__
#define __ACTOR_H__

#include"vector.h"
#include<vector>

class GameStage;
class Component;
class InputManager;
enum Direction;

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
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	void ProcessInput(InputManager*);
	virtual void ActorInput(InputManager*);
	GameStage* GetGameStage() { return mGameStage; }
	void AddComponent(Component*);
	void RemoveComponent(Component*);
	Direction GetDirection() { return dir; }
	void SetMoveFlag() { moveflag = true; }
	bool GetMoveFlag() { return moveflag; }
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	std::vector<Component*> mComponents;
	GameStage* mGameStage;
protected:
	Direction dir;
	bool moveflag;
};

#endif
