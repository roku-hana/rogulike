#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

//�O���錾
class SceneManager;
class InputManager;

//�V�[���̊��N���X
class Scene {
protected:
	SceneManager* sceneManager;			//�������|�C���^�ɂ��邱�ƂőO���錾�����p�ł��� SceneManager sceneManager�ł̓G���[�ɂȂ�
public:
	Scene(SceneManager* pManager) { sceneManager = pManager; }
	//cpp�t�@�C���̂ق��Ɋ֐��̒�`�������Ȃ��ꍇ�̓w�b�_�t�@�C���̂ق��ɕK���A�֐��̒�`�������Ȃ���΂Ȃ�Ȃ��B({}�̒��g����ł�)
	//�֐��̏����͌p����̃N���X�ɏ�������virtual�����āA��`�͋�ɂ��Ă���
	virtual ~Scene() {};
	virtual void update() {};
	virtual void draw() {};
};

//�V�[���Ǘ��N���X
class SceneManager {
public:
	InputManager* input;
	Scene* scene;		//���݂̃V�[���̃|�C���^
	SceneManager();
	~SceneManager();
	void update();
	void draw() { scene->draw(); }
};

#endif

