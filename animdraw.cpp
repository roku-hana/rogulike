#include"animdraw.h"
#include<DxLib.h>

//グラフィックハンドルのセット
int AnimDraw::SetImage(unsigned int apid, int ghandle) {
	if (apid >= aplist.size()) {
		aplist.push_back(animpat());  //新しいアニメパターンの追加
		apid = aplist.size() - 1;    //apidが追加したアニメパターンを指すように調整
	}
	aplist.at(apid).ghlist.push_back(ghandle);
	return apid;
}

//アニメーションギャップのセット(1コマの表示間隔)
int AnimDraw::SetGap(unsigned int apid, int gap) {
	if (apid >= aplist.size()) {
		aplist.push_back(animpat());
		apid = aplist.size() - 1;
	}
	aplist.at(apid).animgap = gap;
	return apid;
}

/*引数apidで指定されたアニメパターンの画像数が1枚ならアニメーションさせる必要なし。よって、単純にアニメパターンの最初の画像(ghlist.at(0))を表示
複数の画像が登録されている場合は、animcounter ÷ 1コマの表示間隔 % コマ数の計算で表示すべきインデックスを求め、その画像を表示*/

//アニメーション描画
void AnimDraw::DrawAnimation(int apid, int x, int y, bool ismoving) {
	if (aplist.at(apid).ghlist.size() > 1) { //コマ数の確認
		int curpat = 0;
		if (ismoving) curpat = GameStage::getAnimCounter() / aplist.at(apid).animgap % aplist.at(apid).ghlist.size();
		DrawGraph(x, y, aplist.at(apid).ghlist.at(curpat), TRUE);
	}
	else {
		DrawGraph(x, y, aplist.at(apid).ghlist.at(0), TRUE);
	}
}

//アニメーション左右(上下)反転描画
void AnimDraw::DrawTurnAnimation(int apid, int x, int y, Direction dir) {
	if (aplist.at(apid).ghlist.size() > 1) { //コマ数の確認
		int curpat = GameStage::getAnimCounter() / aplist.at(apid).animgap % aplist.at(apid).ghlist.size();
		if (dir == RIGHT || dir == DOWN) DrawGraph(x, y, aplist.at(apid).ghlist.at(curpat), true);
		if (dir == LEFT || dir == UP) DrawTurnGraph(x, y, aplist.at(apid).ghlist.at(curpat), true);
	}
	else {
		DrawGraph(x, y, aplist.at(apid).ghlist.at(0), true);
	}
}

//アニメーション回転描画
void AnimDraw::DrawRotaAnimation(int apid, int x, int y, float rad) {
	if (aplist.at(apid).ghlist.size() > 1) {
		int curpat = GameStage::getAnimCounter() / aplist.at(apid).animgap % aplist.at(apid).ghlist.size();
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).ghlist.at(curpat), TRUE, FALSE);
	}
	else {
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).ghlist.at(0), TRUE, FALSE);
	}
}