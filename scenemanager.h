#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

//前方宣言
class SceneManager;
class InputManager;

//シーンの基底クラス
class Scene {
protected:
	SceneManager* sceneManager;			//ここをポインタにすることで前方宣言が利用できる SceneManager sceneManagerではエラーになる
public:
	Scene(SceneManager* pManager) { sceneManager = pManager; }
	//cppファイルのほうに関数の定義を書かない場合はヘッダファイルのほうに必ず、関数の定義をかかなければならない。({}の中身が空でも)
	//関数の処理は継承先のクラスに書くからvirtualをつけて、定義は空にしておく
	virtual ~Scene() {};
	virtual void update() {};
	virtual void draw() {};
};

//シーン管理クラス
class SceneManager {
public:
	InputManager* input;
	Scene* scene;		//現在のシーンのポインタ
	SceneManager();
	~SceneManager();
	void update();
	void draw() { scene->draw(); }
};

#endif

