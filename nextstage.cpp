#include"nextstage.h"
#include<DxLib.h>
#include"play.h"

NextStage::NextStage(SceneManager* sManager, int num) :
	Scene(sManager) {
	SetFontSize(40);                             //サイズを20に変更
	SetFontThickness(1);                         //太さを1に変更
	//ChangeFont, ChangeFontTypeは負荷の重い処理だから頻繁に使わないほうがいい
	ChangeFont("HGS創英角ﾎﾟｯﾌﾟ体");              //HGS創英角ﾎﾟｯﾌﾟ体に変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);//アンチエイリアス＆エッジ付きフォントに変更
	stageNum = num;
	count = GetNowCount();
}

NextStage::~NextStage() {
	SetFontSize(16);
	SetFontThickness(1);
	//ChangeFont, ChangeFontTypeは負荷の重い処理だから頻繁に使わないほうがいい
	ChangeFont("デフォルト");
	ChangeFontType(DX_FONTTYPE_NORMAL);
}

void NextStage::update() {
	if (GetNowCount() - count >= 3000) {		//3秒たったらプレイ画面へ戻る
		sceneManager->scene = new Game(sceneManager, sceneManager->input);
		delete this;
	}
}

void NextStage::draw() {
	DrawFormatString(250, 200, GetColor(255, 255, 255), "地下%d階",stageNum);
}