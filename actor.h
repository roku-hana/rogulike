#ifndef __ACTOR_H__
#define __ACTOR_H__

#include"vector.h"
#include<vector>

enum ActState {
	KEY_INPUT,
	ACT_BEGIN,
	ACT_END,
	MOVE_BEGIN,
	MOVE_END,
	WAIT, 
	ANIMATION
};

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
	void SetDirection(Direction dir) { this->dir = dir; }
	void SetMoveFlag(bool flag) { moveflag = flag; }
	bool GetMoveFlag() { return moveflag; }
	void SetDamageFlag(bool flag) { damageflag = flag; }
	bool GetDamageFlag() { return damageflag; }
	void SetDamageAmount(int damageAmount) { this->damageAmount = damageAmount; }
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	std::vector<Component*> mComponents;
	GameStage* mGameStage;
	bool damageflag;
protected:
	Direction dir;
	bool moveflag;
	int damageAmount;
};

#endif
