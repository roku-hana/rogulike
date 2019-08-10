#ifndef __ANIMDRAW_H__
#define __ANIMDRAW_H__

#include<vector>
using namespace std;

enum Direction {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
	NONE
};

class AnimDraw {
private:
	struct animpat {
		vector<int> ghlist;
		int animgap; //表示間隔(この値を大きくすると、アニメーションが遅くなり、小さくすると速くなる)
		animpat() { animgap = 1; }
	};
	vector<animpat> aplist;
public:
	AnimDraw() { aplist.push_back(animpat()); }
	//apidはアニメパターンの番号、つまりメンバ変数aplistのインデックスを表している
	int SetImage(unsigned int apid, int ghandle);  //グラフィックハンドルをセットする
	int SetGap(unsigned int apid, int gap);  //表示間隔(animagp)をセットする
	void DrawAnimation(int apid, int x, int y, int count);  //アニメーション表示
	void DrawTurnAnimation(int apid, int x, int y, int count, Direction dir);  //アニメーション左右反転
	void DrawRotaAnimation(int apid, int x, int y, int count, float rad);  //アニメーション回転表示
};

#endif
