#ifndef __TITLE_H__
#define __TITLE_H__

#include"scenemanager.h"

class Title : public Scene {
private:
	int back;
public:
	Title(SceneManager* pt);
	~Title() {};
	void draw();
	void update();
};

#endif