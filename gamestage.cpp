#include"gamestage.h"
#include"makedungeon.h"
#include"spritecomponent.h"
#include"player.h"
#include"chick.h"
#include"collision.h"
#include"boar.h"
#include<fstream>

GameStage::GameStage(InputManager* temp):input(temp) {
	mp = new MapData();
	player = new Player(this, mp->GetMap());
	player->SetScrollX(mp->GetStartX() * CHIPSIZE);
	player->SetScrollY(mp->GetStartY() * CHIPSIZE);
	for (int i = 0; i < mp->GetChickNum(); i++) {
		new Chick(this, mp->GetChickX(i), mp->GetChickY(i), player->GetScrollX(), player->GetScrollY());
	}

	//enemyParam
	string fileName = "enemydata\\enemydata" + std::to_string(mp->GetStageNum()) + ".csv";
	LoadEnemyParam(fileName.c_str());
	for (int i = 0; i < mp->GetEnemyNum(); i++) {
		switch (enemyParam[i].id) {
		case 0: new Boar(this, mp->GetMap(), mp->GetEnemyX(i), mp->GetEnemyY(i), player->GetScrollX(), player->GetScrollY(), enemyParam[i]); break;
		default: break;
		}
	}
	//

	nextStage = 0;
	colManager = new Collision(this);

	LoadMessage();
}

GameStage::~GameStage() {
	delete player;
	delete mp;
	delete colManager;
}

void GameStage::update() {
	animcounter++;
	if (*player->GetScrollX() / CHIPSIZE == mp->GetGoalX() && *player->GetScrollY() / CHIPSIZE == mp->GetGoalY()) nextStage = mp->GetStageNum() + 1;
	else nextStage = 0;

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

	colManager->Player_Chick_Collision();
}

void GameStage::draw() {
	mp->draw(*player->GetScrollX(), *player->GetScrollY());
	mp->DrawTransparentMaze(*player->GetScrollX() / CHIPSIZE, *player->GetScrollY() / CHIPSIZE);
	//mp->DrawTempMap();

	for (auto sprite : mSprites)
	{
		sprite->Draw(animcounter);
	}
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
	}
}

void GameStage::LoadMessage() {
	std::string temp;
	ifstream fp("テキストファイル.txt");
	if (fp.fail()) MSG("ファイル読み込みエラー");
	while (std::getline(fp, temp)) messages.push_back(temp);
}

std::string& GameStage::Get_Message(int i, std::string& pl, std::string& en, int val) {
	//テキストファイルの中のタグを引数の文字列に置換する
	message = messages[i];
	auto pos1 = message.find("<pl>");
	auto len1 = 4;
	if (pos1 != std::string::npos) message.replace(pos1, len1, pl);
	auto pos2 = message.find("<en>");
	auto len2 = 4;
	if (pos2 != std::string::npos) message.replace(pos2, len2, en);
	auto pos3 = message.find("<val>");
	auto len3 = 5;
	if (pos3 != std::string::npos) message.replace(pos3, len3, std::to_string(val));

	return message;
}

void GameStage::LoadEnemyParam(const char* fileName) {
	//ここで、EnemyParamをファイルから格納
	FILE* fp;
	char buf[50];
	int c;
	int col = 1;
	EnemyParameter temp;

	memset(buf, 0, sizeof(buf));
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