#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class Actor;
class InputManager;

class Component {
public:
	//updateOrderが小さいコンポーネントほど早く更新される
	Component(Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void update();
	int getUpdateOrder() const {return mUpdateOrder; }
	virtual void ProcessInput(InputManager* temp) {}
protected:
	Actor* mOwner;
	int mUpdateOrder;
};

#endif
