#include"inventorycomponent.h"
#include"player.h"
#include"gamestage.h"
#include"item.h"
#include"iteminventorysprite.h"
#include<DxLib.h>
#include"input.h"

InventoryComponent::InventoryComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	player = (Player*)owner;
	ItemInventorySprite* iic = new ItemInventorySprite(player, 100, this);
	cursole.y = 75;
	cursole.x = 53;
	cursole.r = 2;
	cursole.pos = 0;
	flag = false;
	imk = I_NONE;
	cursole2.y = 115;
	cursole2.x = 405;
	cursole2.r = 2;
	cursole2.pos = 0;
	imk2 = IS_NONE;
}

void InventoryComponent::update() {
	for (auto item : player->GetGameStage()->GetItems()) {
		if(item->GetMoveFlag() && !item->GetDamageFlag()){
			items.push_back(item);
			item->SetDamageFlag(true);
		}
	}
	if (player->GetActState() == ITEM_MENU) {
		Belongings();
		Others();
	}
}

void InventoryComponent::ProcessInput(InputManager* input) {
	if (player->GetActState() == ITEM_MENU) {
		if (input->isPushUp()){
			if (imk == BELONGINGS_USE) { 
				if (cursole2.pos != 0) { cursole2.pos--; cursole2.y -= 20; }
			}
			else {
				if (cursole.pos != 0) { cursole.pos--; cursole.y -= 20; }
			}
		}
		if (input->isPushDown()) {
			if (imk == BELONGINGS_USE) {
				if (cursole2.pos != 3) { cursole2.pos++; cursole2.y += 20; }
			}
			else {
				if(imk == BELONGINGS){
					if (cursole.pos != items.size() - 1 && items.size() != 0) { cursole.pos++; cursole.y += 20; }
				}
				else {
					if (cursole.pos != 1) { cursole.pos++; cursole.y += 20; }
				}
			}
		}
		if (input->isPushA()) {
			if (imk == I_NONE) flag = true;
			if (imk == BELONGINGS || imk == OTHERS) { ResetCursole(); }
			if (imk == BELONGINGS_USE) { imk = BELONGINGS; ResetCursole2(); }
		}
		if(flag){
			player->SetActState(KEY_INPUT);
			flag = false;
			ResetCursole();
			ResetCursole2();
		}
		if (input->isPushB()) {
			if (imk == BELONGINGS_USE) {
				switch (cursole2.pos) {
				case 0: imk2 = USE; break;
				case 1: imk2 = PUT; break;
				case 2: imk2 = THROW; break;
				case 3: imk2 = EXPLANATION; break;
				default: break;
				}
			}
			else if (imk == BELONGINGS) {
				if (items.size() > 0) {
					imk = BELONGINGS_USE;
					cursole2.pos = 0;
					cursole2.y = 115; cursole2.x = 405;
				}
			}
			else if (imk == I_NONE) {
				switch (cursole.pos) {
				case 0: imk = BELONGINGS; cursole.pos = 0; cursole.x = 105; cursole.y = 135; break;
				case 1: imk = OTHERS; cursole.pos = 0; break;
				default: break;
				}
			}
		}
	}
}

void InventoryComponent::Belongings() {
	switch (imk2) {
	case USE:
		if (items[cursole.pos]->GetCategory() == 1) {
			items[cursole.pos]->Use();
			items[cursole.pos]->SetState(Actor::DEAD);
			items.erase(items.begin() + cursole.pos);
			items.shrink_to_fit();
		}
		else if(items[cursole.pos]->GetCategory() == 2){
			if (!items[cursole.pos]->GetEquip()) {
				for (auto item : items) if (item->GetEquip() && item->GetCategory() == 2) item->Off();
				items[cursole.pos]->Use();
			}
			else items[cursole.pos]->Off();
		}
		else  if (items[cursole.pos]->GetCategory() == 3) {
			if (!items[cursole.pos]->GetEquip()) {
				for (auto item : items) if (item->GetEquip() && item->GetCategory() == 3) item->Off();
				items[cursole.pos]->Use();
			}
			else items[cursole.pos]->Off();
		}
		flag = true;
		break;
	case PUT:
		items[cursole.pos]->Put(*player->GetScrollX() / 32, *player->GetScrollY() / 32);
		items.erase(items.begin() + cursole.pos);
		items.shrink_to_fit();
		flag = true;
		break;
	case THROW:
		items[cursole.pos]->Throw(*player->GetScrollX() / 32, *player->GetScrollY() / 32, player->GetDirection());
		items.erase(items.begin() + cursole.pos);
		items.shrink_to_fit();
		flag = true;
		break;
	default: break;
	}
}

void InventoryComponent::Others() {
	if (imk == OTHERS) {
		//‚±‚±‚Å‚ÍA‚»‚Ì‘¼‚Ì‚»‚ê‚¼‚ê‚Ìˆ—‚ğs‚¤
	}
}

void InventoryComponent::ResetCursole() {
	imk = I_NONE;
	cursole.pos = 0; 
	cursole.y = 75; 
	cursole.x = 53;
}

void InventoryComponent::ResetCursole2() {
	imk2 = IS_NONE;
	cursole2.pos = 0; 
	cursole2.y = 115; 
	cursole2.x = 405;
}