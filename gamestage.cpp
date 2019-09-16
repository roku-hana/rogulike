#include"gamestage.h"
#include"makedungeon.h"
#include"spritecomponent.h"
#include"player.h"
#include"chick.h"
#include"collision.h"
#include"boar.h"
#include"goblin.h"
#include"recovery.h"
#include"weapon.h"
#include"protection.h"
#include<fstream>
//メッセージの描画のためだけにDxライブラリを描画するのはどうなんだろう
#include<DxLib.h>
//

float frand() {
	return (float)GetRand(RAND_MAX) / RAND_MAX;
}

GameStage::GameStage(InputManager* temp):input(temp){
	mp = new MapData();
	player = new Player(this, mp->GetMap());
	player->SetScrollX(mp->GetStartX() * CHIPSIZE);
	player->SetScrollY(mp->GetStartY() * CHIPSIZE);
	for (int i = 0; i < mp->GetChickNum(); i++) {
		new Chick(this, mp->GetChickX(i), mp->GetChickY(i), player->GetScrollX(), player->GetScrollY());
	}
	if(stageNum == 0) stageNum = 1;
	//enemyParam
	string fileName = "enemydata\\enemydata" + std::to_string(stageNum) + ".csv";
	LoadEnemyParam(fileName.c_str());
	InitializeEnemy();
	//
	//itemdata
	fileName = "itemdata\\protection" + std::to_string(stageNum) + ".csv";
	LoadProtectionItem(fileName.c_str());
	fileName = "itemdata\\weapon" + std::to_string(stageNum) + ".csv";	
	LoadWeaponItem(fileName.c_str());
	fileName = "itemdata\\recovery" + std::to_string(stageNum) + ".csv";
	LoadRecoveryItem(fileName.c_str());
	InitializeItem();
	//
	nextStage = 0;
	colManager = new Collision(this);

	messagebox = LoadGraph("Images\\messagebox.png");
	LoadMessage();
	gameover = false;
}

GameStage::~GameStage() {
	delete mp;
	delete colManager;
}

void GameStage::update() {
	animcounter++;
	if (*player->GetScrollX() / CHIPSIZE == mp->GetGoalX() && *player->GetScrollY() / CHIPSIZE == mp->GetGoalY()) {
		if (nextStage == 0) player->SetActState(WAIT);
		nextStage = stageNum + 1;
	}
	else nextStage = 0;

	EnemyAddTime();

	colManager->Player_Chick_Collision();

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->update();
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::DEAD)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

	PlayerKeyInput();
	colManager->Player_Item_Collision();
}

void GameStage::draw() {
	mp->draw(*player->GetScrollX(), *player->GetScrollY());
	mp->DrawDarkness(*player->GetScrollX() / CHIPSIZE, *player->GetScrollY() / CHIPSIZE);
	mp->DrawTransparentMaze(*player->GetScrollX() / CHIPSIZE, *player->GetScrollY() / CHIPSIZE);

	//仮
	for (auto enemy : mEnemies) mp->DrawEnemyPos(enemy->GetIndexX(), enemy->GetIndexY());

	for (auto item : mItems) if(!item->GetDamageFlag())mp->DrawItemPos(item->GetPosX(), item->GetPosY());
	//

	for (auto sprite : mSprites) sprite->Draw(animcounter);

	//メッセージの描画(別の場所のほうがいいかも)
	DrawMessage();

	DrawStateUp();

	//テスト
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	DrawFormatString(300, 300, GetColor(255, 255, 255), "mouseX:%d", mouseX);
	DrawFormatString(400, 300, GetColor(255, 255, 255), "mouseY:%d", mouseY);
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "enemyNum:%d", enemyNum2);
	//DrawFormatString(100, 150, GetColor(255, 255, 255), "size:%d", mEnemies.size());
	//DrawFormatString(100, 200, GetColor(255, 255, 255), "capacity:%d", mEnemies.capacity());
	///////////////////////////////////////////////////////////////////////////////////////
}

void GameStage::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void GameStage::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void GameStage::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void GameStage::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void GameStage::ProcessInput() {
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(input);
	}
	mUpdatingActors = false;
}

void GameStage::AddChick(Chick* chick) {
	mChicks.emplace_back(chick);
}

void GameStage::RemoveChick(Chick* chick) {
	auto iter = std::find(mChicks.begin(),
		mChicks.end(), chick);
	if (iter != mChicks.end())
	{
		mChicks.erase(iter);
	}
}

void GameStage::AddEnemy(Enemy* enemy) {
	mEnemies.emplace_back(enemy);
}

void GameStage::RemoveEnemy(Enemy* enemy) {
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	if (iter != mEnemies.end()) {
		mEnemies.erase(iter);
		mEnemies.shrink_to_fit();
		enemyNum2--;
	}
}

void GameStage::AddItem(Item* item) {
	mItems.emplace_back(item);
}

void GameStage::RemoveItem(Item* item) {
	auto iter = std::find(mItems.begin(), mItems.end(), item);
	if (iter != mItems.end()) {
		mItems.erase(iter);
		mItems.shrink_to_fit();
	}
}

void GameStage::LoadMessage() {
	std::string temp;
	ifstream fp("テキストファイル.txt");
	if (fp.fail()) MSG("ファイル読み込みエラー");
	while (std::getline(fp, temp)) messages.push_back(temp);
}

void GameStage::SetMessage(int i, std::string& pl, std::string& en, int val) {
	string temp = messages[i];
	auto pos1 = temp.find("<pl>");
	auto len1 = 4;
	if (pos1 != std::string::npos) temp.replace(pos1, len1, pl);
	auto pos2 = temp.find("<en>");
	auto len2 = 4;
	if (pos2 != std::string::npos) temp.replace(pos2, len2, en);
	auto pos3 = temp.find("<val>");
	auto len3 = 5;
	if (pos3 != std::string::npos) temp.replace(pos3, len3, std::to_string(val));

	if (message.size() > 2) {
		message.pop();
	}
	message.push(temp);
}

void GameStage::DrawMessage() {
	if (messageflag) {
		DrawGraph(120, 390, messagebox, TRUE);
		DrawString(130, 420, message.front().c_str(), GetColor(255, 255, 255));
		if (message.size() == 2) DrawString(130, 440, message.back().c_str(), GetColor(255, 255, 255));
		if (message.size() > 2) message.pop();
	}
	else {
		while (!message.empty()) message.pop();
	}
}

void GameStage::LoadEnemyParam(const char* fileName) {
	//ここで、EnemyParamをファイルから格納
	FILE* fp;
	char buf[50] = {};
	int c;
	int col = 1;
	EnemyParameter temp;

	fopen_s(&fp, fileName, "r");
	if (fp == NULL) MSG("ファイル読み込みエラー");

	fscanf_s(fp, "%d", &enemyNum);
	while (fgetc(fp) != '\n');   //改行消す
	//2行目読み飛ばし
	while (fgetc(fp) != '\n');

	while (1) {
		while (1) {
			c = fgetc(fp);
			//ファイルの最後まで来たらループを抜ける
			if (c == EOF) goto out;
			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n') strcat_s(buf, sizeof(buf), (const char*)& c);
			else break;
		}
		switch (col) {
		case 1: temp.id = atoi(buf); break;
		case 2: temp.nowhp = atoi(buf); break;
		case 3: temp.maxhp = atoi(buf); break;
		case 4: temp.attack = atoi(buf); break;
		case 5: temp.defense = atoi(buf); break;
		case 6: temp.experiense = atoi(buf); break;
		default: break;
		}
		memset(buf, 0, sizeof(buf));
		col++;
		if (c == '\n') {
			enemyParam.push_back(temp);
			col = 1;
		}
	}
	out:
	fclose(fp);
}

void GameStage::InitializeEnemy() {
	enemyNum2 = mp->GetEnemyNum();
	for (int i = 0; i < enemyNum2; i++) {
		int knd = GetRand(enemyNum - 1);
		knd = enemyParam[knd].id;
		eposx.push_back(mp->GetEnemyX(i));
		eposy.push_back(mp->GetEnemyY(i));
		switch (knd) {
		case 0: new Boar(this, mp->GetMap(), eposx[i], eposy[i], player->GetScrollX(), player->GetScrollY(), enemyParam[knd]); break;
		case 1: new Goblin(this, mp->GetMap(), eposx[i], eposy[i], player->GetScrollX(), player->GetScrollY(), enemyParam[knd]); break;
		default: break;
		}
	}
}

void GameStage::PlayerKeyInput() {
	if (player->GetActState() == MOVE_END || player->GetActState() == ACT_END) {
		bool flag = false;
		for (auto enemy : mEnemies) {
			if (enemy->GetActState() == ACT_END || enemy->GetActState() == MOVE_END) flag = true;
			else { flag = false; break; }
		}
		if (flag) {
			messageflag = false;
			if (!player->GetMoveFlag()) { player->SetMoveFlag(true); }
			player->SetActState(KEY_INPUT);
			//for (auto enemy : mEnemies) if(enemy->GetCount() >= 60) enemy->SetCount60();
			//for (auto enemy : mEnemies) enemy->SetCount0();
			sort(mEnemies.begin(), mEnemies.end(), &PlayerEnemyDisComp);
			for (int i = 0; i < mEnemies.size(); i++) mEnemies[i]->SetWaitTime(i);
		}
		if (mEnemies.size() == 0) player->SetActState(KEY_INPUT);
	}
}

void GameStage::EnemyAddTime() {
	if (enemyNum2 < 15) {
		if (player->GetEnemyAddFlag()) {
			int index = GetRand(eposx.size() - 1);
			int ex = eposx[index];
			int ey = eposy[index];
			int knd = GetRand(enemyParam.size() - 1);
			knd = enemyParam[knd].id;
			switch (knd) {
			case 0: new Boar(this, mp->GetMap(), ex, ey, player->GetScrollX(), player->GetScrollY(), enemyParam[knd]); break;
			case 1: new Goblin(this, mp->GetMap(), ex, ey, player->GetScrollX(), player->GetScrollY(), enemyParam[knd]); break;
			default: break;
			}
			enemyNum2++;
			player->SetEnemyAddFlag(false);
		}
	}
}

void GameStage::LoadProtectionItem(const char* fileName) {
	FILE* fp;
	char buf[50] = {};
	int c;
	int col = 1;
	ItemData temp;

	fopen_s(&fp, fileName, "r");
	if (fp == NULL) MSG("ファイル読み込みエラー");

	fscanf_s(fp, "%d", &pNum);
	while (fgetc(fp) != '\n');   //改行消す
	//2行目読み飛ばし
	while (fgetc(fp) != '\n');

	while (1) {
		while (1) {
			c = fgetc(fp);
			//ファイルの最後まで来たらループを抜ける
			if (c == EOF) goto out;
			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n') strcat_s(buf, sizeof(buf), (const char*)& c);
			else break;
		}
		switch (col) {
		case 1: temp.id = atoi(buf); break;
		case 2: temp.name = buf; break;
		case 3: temp.category = atoi(buf); break;
		case 4: temp.val = atoi(buf); break;
		case 5: temp.explanation = buf; break;
		case 6: temp.probability = atof(buf); break;
		default: break;
		}
		memset(buf, 0, sizeof(buf));
		col++;
		if (c == '\n') {
			protectiondata.push_back(temp);
			col = 1;
		}
	}
out:
	fclose(fp);
}

void GameStage::LoadWeaponItem(const char* fileName) {
	FILE* fp;
	char buf[50] = {};
	int c;
	int col = 1;
	ItemData temp;

	fopen_s(&fp, fileName, "r");
	if (fp == NULL) MSG("ファイル読み込みエラー");

	fscanf_s(fp, "%d", &wNum);
	while (fgetc(fp) != '\n');   //改行消す
	//2行目読み飛ばし
	while (fgetc(fp) != '\n');

	while (1) {
		while (1) {
			c = fgetc(fp);
			//ファイルの最後まで来たらループを抜ける
			if (c == EOF) goto out;
			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n') strcat_s(buf, sizeof(buf), (const char*)& c);
			else break;
		}
		switch (col) {
		case 1: temp.id = atoi(buf); break;
		case 2: temp.name = buf; break;
		case 3: temp.category = atoi(buf); break;
		case 4: temp.val = atoi(buf); break;
		case 5: temp.explanation = buf; break;
		case 6: temp.probability = atof(buf); break;
		default: break;
		}
		memset(buf, 0, sizeof(buf));
		col++;
		if (c == '\n') {
			weapondata.push_back(temp);
			col = 1;
		}
	}
out:
	fclose(fp);
}

void GameStage::LoadRecoveryItem(const char* fileName) {
	FILE* fp;
	char buf[50] = {};
	int c;
	int col = 1;
	ItemData temp;

	fopen_s(&fp, fileName, "r");
	if (fp == NULL) MSG("ファイル読み込みエラー");

	fscanf_s(fp, "%d", &rNum);
	while (fgetc(fp) != '\n');   //改行消す
	//2行目読み飛ばし
	while (fgetc(fp) != '\n');

	while (1) {
		while (1) {
			c = fgetc(fp);
			//ファイルの最後まで来たらループを抜ける
			if (c == EOF) goto out;
			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n') strcat_s(buf, sizeof(buf), (const char*)& c);
			else break;
		}
		switch (col) {
		case 1: temp.id = atoi(buf); break;
		case 2: temp.name = buf; break;
		case 3: temp.category = atoi(buf); break;
		case 4: temp.val = atoi(buf); break;
		case 5: temp.explanation = buf; break;
		case 6: temp.probability = atof(buf); break;
		default: break;
		}
		memset(buf, 0, sizeof(buf));
		col++;
		if (c == '\n') {
			recoverydata.push_back(temp);
			col = 1;
		}
	}
out:
	fclose(fp);
}

void GameStage::InitializeItem() {
	for (int i = 0; i < mp->GetItemNum(); i++) {
		ITEM_KND knd = (ITEM_KND)GetRand(2);
		switch (knd) {
		case RECOVERY: 
			new Recovery(this, mp->GetMap(), mp->GetItemX(i), mp->GetItemY(i), &RandomRecoveryPick());
			break;
		case WEAPON: 
			new Weapon(this, mp->GetMap(), mp->GetItemX(i), mp->GetItemY(i), &RandomWeaponPick());
			break;
		case PROTECTION: 
			new Protection(this, mp->GetMap(), mp->GetItemX(i), mp->GetItemY(i), &RandomProtectionPick());
			break;
		default: break;
		}
	}
}

ItemData GameStage::RandomProtectionPick() {
	float totalProbability = 0.0f;
	for (auto protection : protectiondata) {
		totalProbability += protection.probability;
	}
	float probability = totalProbability * frand();
	float cumulativeProbability = 0.0f;
	for (auto protection : protectiondata) {
		cumulativeProbability += protection.probability;
		if (probability < cumulativeProbability) return protection;
	}
}

ItemData GameStage::RandomWeaponPick() {
	float totalProbability = 0.0f;
	for (auto weapon : weapondata) {
		totalProbability += weapon.probability;
	}
	float probability = totalProbability * frand();
	float cumulativeProbability = 0.0f;
	for (auto weapon : weapondata) {
		cumulativeProbability += weapon.probability;
		if (probability < cumulativeProbability) return weapon;
	}
}

ItemData GameStage::RandomRecoveryPick() {
	float totalProbability = 0.0f;
	for (auto recovery : recoverydata) {
		totalProbability += recovery.probability;
	}
	float probability = totalProbability * frand();
	float cumulativeProbability = 0.0f;
	for (auto recovery : recoverydata) {
		cumulativeProbability += recovery.probability;
		if (probability < cumulativeProbability) return recovery;
	}
}

bool GameStage::PlayerEnemyDisComp(const Enemy* a, const Enemy* b) {
	int disax = abs(a->GetEpx());
	int disay = abs(a->GetEpy());
	int disbx = abs(b->GetEpx());
	int disby = abs(b->GetEpy());

	return disax + disay < disbx + disby;
}

void GameStage::DrawStateUp() {
	DrawFormatString(190, 0, GetColor(255, 255, 255), "%d", stageNum);
	DrawString(200, 0, "F", GetColor(128, 255, 255));
	DrawString(230, 0, "HP    /", GetColor(126, 255, 255));
	DrawFormatString(260, 0, GetColor(255, 255, 255), "%d", player->GetPlayerParam().nowhp);
	DrawFormatString(300, 0, GetColor(255, 255, 255), "%d", player->GetPlayerParam().maxhp);
	DrawString(350, 0, "Lv", GetColor(128, 255, 255));
	DrawFormatString(380, 0, GetColor(255, 255, 255), "%d", player->GetPlayerParam().level);
	DrawGraph(400, 0, chickGh, TRUE);
	DrawFormatString(420, 0, GetColor(255, 255, 255), "×%d", player->GetChickNum());

}

ResultInfo GameStage::ri;
int GameStage::stageNum;