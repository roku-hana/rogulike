#include"iteminventorysprite.h"
#include<DxLib.h>
#include"inventorycomponent.h"
#include"player.h"
#include"item.h"

ItemInventorySprite::ItemInventorySprite(Actor* owner, int drawOrder, InventoryComponent* ic) 
:SpriteComponent(owner, drawOrder),
ic(ic)
{
	player = (Player*)owner;
	smallfont = CreateFontToHandle(NULL, 10, 3);
	weapon = LoadGraph("Images\\item\\アイコン\\icon002.png");
	recovery = LoadGraph("Images\\item\\アイコン\\icon030.png");
	protection = LoadGraph("Images\\item\\アイコン\\icon010.png");
}

void ItemInventorySprite::Draw(int count) {
	//menu, belongings, othersをそれぞれ四角形、カーソル、文字ここですべて描画
	if (player->GetActState() == ITEM_MENU) {
		switch (ic->GetItemMenuKnd()) {
		case I_NONE: DrawMenu(); break;
		case BELONGINGS: DrawBelongings(); break;
		case BELONGINGS_USE: 
			if (ic->GetItemSubMenuKnd() == EXPLANATION) { DrawExplanation(); }
			else { DrawBelongings(); DrawBelongingsUse(); } 
			break;
		case OTHERS: DrawOthers(); break;
		default: break;
		}
	}
}

void ItemInventorySprite::DrawMenu() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(45, 45, 130, 130, GetColor(0, 0, 51), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(45, 45, 130, 130, GetColor(255, 255, 255), FALSE);
	//DrawFormatString(50, 50, GetColor(255, 255, 255), "メニュー", smallfont);
	DrawFormatString(50, 50, GetColor(255, 255, 255), "メニュー");
	DrawLine(45, 65, 130, 65, GetColor(255, 255, 255));
	//DrawFormatString(60, 70, GetColor(255, 255, 255), "持ち物", smallfont);
	DrawFormatString(60, 70, GetColor(255, 255, 255), "持ち物");
	//DrawFormatString(60, 90, GetColor(255, 255, 255), "その他", smallfont);
	DrawFormatString(60, 90, GetColor(255, 255, 255), "その他");
	DrawCircle(ic->GetCursole().x, ic->GetCursole().y, ic->GetCursole().r, GetColor(255, 255, 255), TRUE);
}

void ItemInventorySprite::DrawBelongings() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(100, 100, 300, 300, GetColor(0, 0, 51), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(100, 100, 300, 300, GetColor(255, 255, 255), FALSE);
	//DrawFormatString(105, 105, GetColor(255, 255, 255), "持ち物", smallfont);
	DrawFormatString(105, 105, GetColor(255, 255, 255), "持ち物");
	DrawLine(100, 120, 300, 120, GetColor(255, 255, 255));
	for (int i = 0; i < ic->GetItems().size(); i++) {
		switch (ic->GetItems()[i]->GetCategory()) {
		case 1: DrawGraph(130, 125 + i * 20, recovery, TRUE); break;
		case 2: 
			DrawGraph(130, 125 + i * 20, weapon, TRUE); 
			if (ic->GetItems()[i]->GetEquip()) DrawStringToHandle(120, 120 + i * 20, "E", GetColor(255, 255, 255), smallfont);
			break;
		case 3: 
			DrawGraph(130, 125 + i * 20, protection, TRUE); 
			if (ic->GetItems()[i]->GetEquip()) DrawStringToHandle(120, 120 + i * 20, "E", GetColor(255, 255, 255), smallfont);
			break;
		default: break;
		}
		DrawString(160, 125 + i * 20, ic->GetItems()[i]->GetName().c_str(), GetColor(255, 255, 255));
	}
	DrawCircle(ic->GetCursole().x, ic->GetCursole().y, ic->GetCursole().r, GetColor(255, 255, 255), TRUE);
}

void ItemInventorySprite::DrawBelongingsUse() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(400, 100, 500, 190, GetColor(0, 0, 51), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(400, 100, 500, 190, GetColor(255, 255, 255), FALSE);
	switch (ic->GetItems()[ic->GetCursole().pos]->GetCategory()) {
	case 1: DrawString(415, 105, "使う", GetColor(255, 255, 255)); break;
	case 2:
		if (!ic->GetItems()[ic->GetCursole().pos]->GetEquip()) DrawString(415, 105, "装備", GetColor(255, 255, 255));
		else DrawString(415, 105, "はずす", GetColor(255, 255, 255));
		break;
	case 3:
		if (!ic->GetItems()[ic->GetCursole().pos]->GetEquip()) DrawString(415, 105, "装備", GetColor(255, 255, 255));
		else DrawString(415, 105, "はずす", GetColor(255, 255, 255));
			break;
	default: break;
	}
	DrawString(415, 125, "置く", GetColor(255, 255, 255));
	DrawString(415, 145, "投げる", GetColor(255, 255, 255));
	DrawString(415, 165, "説明", GetColor(255, 255, 255));
	DrawCircle(ic->GetCursole2().x, ic->GetCursole2().y, ic->GetCursole2().r, GetColor(255, 255, 255), TRUE);
}

void ItemInventorySprite::DrawExplanation() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(200, 100, 400, 300, GetColor(0, 0, 51), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(200, 100, 400, 300, GetColor(255, 255, 255), FALSE);
	DrawString(210, 110, ic->GetItems()[ic->GetCursole().pos]->GetExplanation().c_str(), GetColor(255, 255, 255));
}

void ItemInventorySprite::DrawOthers() {
	
}