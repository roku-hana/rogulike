#include"item.h"
#include"gamestage.h"
#include"animdraw.h"
#include"makedungeon.h"
#include"player.h"

const int DRAW_PLAYER_X = 320;
const int DRAW_PLAYER_Y = 224;

Item::Item(GameStage* game, vector<vector<RogueLikeMap>>& map, int x, int y) 
	:Actor(game), mapdata(map),
	posx(x), posy(y)
{
	game->AddItem(this);
	throwflag = false;
	count = 0;
}

Item::~Item() {
	GetGameStage()->RemoveItem(this);
}

void Item::updateActor() {
	if (throwflag) {
		Vector2 add = {};
		int x = posx - addx;
		int y = posy - addy;
		add.x -= sin(3.14 / 2 / 30 * count) * x;
		add.y -= sin(3.14 / 2 / 30 * count) * y;
		SetPosition(Vector2(DRAW_PLAYER_X + add.x * CHIPSIZE + 6, DRAW_PLAYER_Y + add.y * CHIPSIZE + 12));
		if (count < 30) count++;
		else{
			count = 0;
			posx -= x;
			posy -= y;
			throwflag = false;
		}
	}
	int ipx = posx - *GetGameStage()->GetPlayer()->GetScrollX() / CHIPSIZE;
	int ipy = posy - *GetGameStage()->GetPlayer()->GetScrollY() / CHIPSIZE;
	Vector2 setpos = { (float)DRAW_PLAYER_X + ipx * CHIPSIZE + 6, (float)DRAW_PLAYER_Y + ipy * CHIPSIZE + 12};
	if (!throwflag) {
		if (isDraw(ipx, ipy) && !moveflag) {
			SetPosition(setpos);
		}
		else SetPosition(Vector2(-100, -100));
	}

	if (!moveflag && GetDamageFlag()) {
		if (abs(ipx) == 1 || abs(ipy) == 1) { 
			SetDamageFlag(false); 
		}
	}
}

void Item::Throw(int px, int py, Direction pdir) {
	posx = px;
	posy = py;
	switch (pdir) {
	case UP: 
		while(mapdata[py][px].mapData != 1) py--;
		moveflag = false;
		addy = py + 1; addx = px; throwflag = true;
		break;
	case DOWN:
		while(mapdata[py][px].mapData != 1) py++;
		moveflag = false;
		addy = py - 1; addx = px; throwflag = true;
		break;
	case RIGHT:
		while (mapdata[py][px].mapData != 1) px++;
		moveflag = false;
		addy = py; addx = px - 1; throwflag = true;
		break;
	case LEFT:
		while (mapdata[py][px].mapData != 1) px--;
		moveflag = false;
		addy = py; addx = px + 1; throwflag = true;
		break;
	case UP_RIGHT:
		while (mapdata[py][px].mapData != 1) { py--; px++; }
		moveflag = false;
		addy = py + 1; addx = px - 1; throwflag = true;
		break;
	case UP_LEFT:
		while (mapdata[py][px].mapData != 1) { py--; px++; }
		moveflag = false;
		addy = py + 1; addx = px - 1; throwflag = true;
		break;
	case DOWN_RIGHT:
		while (mapdata[py][px].mapData != 1) { py++; px++; }
		moveflag = false;
		addy = py - 1; addx = px - 1; throwflag = true;
		break;
	case DOWN_LEFT:
		while (mapdata[py][px].mapData != 1) { py++; px--; }
		moveflag = false;
		addy = py - 1; addx = px + 1; throwflag = true;
		break;
	default: break;
	}
}

void Item::Put(int px, int py) {
	moveflag = false;
	posx = px;
	posy = py;
}

bool Item::isDraw(int x, int y) {
	int py = *GetGameStage()->GetPlayer()->GetScrollY() / CHIPSIZE;
	int px = *GetGameStage()->GetPlayer()->GetScrollX() / CHIPSIZE;
	if (GetGameStage()->GetMapData()->GetLightKnd() == 1) {
		if (x >= -1 * DRAW_CHIPNUM_X && x <= DRAW_CHIPNUM_X) {
			if (y >= -1 * DRAW_CHIPNUM_Y && y <= DRAW_CHIPNUM_Y) {
				if (mapdata[posy][posx].mapData == mapdata[py][px].mapData) return true;
			}
		}
	}
	if (GetGameStage()->GetMapData()->GetLightKnd() == 2) {
		if (x >= -1 && x <= 1) {
			if (y >= -1 && y <= 1) {
				return true;
			}
		}
	}
	return false;
}