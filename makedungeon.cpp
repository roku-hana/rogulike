#include "makedungeon.h"
#include<DxLib.h>
#include<queue>

int GetRandomNum(int a, int b) {

	return GetRand(b - a) + a;

}

/*���[�O���C�N�����֐�*/
template <typename T>
int rogueLikeMapMake(DungeonMap_RL* const dng, T& maprl)
{
	if (maprl.size() == 0 || maprl.front().size() == 0) return -1;
	for (size_t i = 0; i < maprl.size(); ++i)
		for (size_t j = 0; j < maprl[i].size(); ++j)
			maprl[i][j].mapData = 1;

	dng->mapDivCount = dng->divCountMin + (size_t)GetRand((int)dng->divCountRand) + 1; //�}�b�v�̋敪���� (�����̌�) 0~n�܂ł̕���ID
	if (dng->mapDivCount > dng->divCountMin + dng->divCountRand) return -1;

	dng->mapDiv[0][0] = (maprl.size() - 1); //�}�b�v�̋敪�������T�C�YX�I�_ (�}�b�v�̑傫��X��)
	dng->mapDiv[0][1] = (maprl.front().size() - 1); //�}�b�v�̋敪�������T�C�YY�I�_ (�}�b�v�̑傫��Y��)
	dng->mapDiv[0][2] = 1; //�}�b�v�̋敪�������T�C�YX�n�_ (�}�b�v�̑傫��X��)
	dng->mapDiv[0][3] = 1; //�}�b�v�̋敪�������T�C�YY�n�_ (�}�b�v�̑傫��Y��)

	dng->mapRoad[0][0] = 255;
	dng->mapRoad[0][1] = 255;

	/*�}�b�v���敪�����Ă�������(���𕪊����鏈��)*/
	size_t divAfter;
	int count; //(0:X, 1:Y) X���ŕ����邩Y���ŕ����邩���߂�

	for (size_t i = 1; i < dng->mapDivCount; ++i) {

		//���܂ō�����敪���������_���Ɏw��(�w�肵����������ɋ敪������)
		divAfter = (size_t)GetRand((int)i - 1);

		//�w�肵������X��Y�̒����ɂ���āA����������������߂�(�����ق��𕪊�����)
		if (dng->mapDiv[divAfter][0] - dng->mapDiv[divAfter][2] > dng->mapDiv[divAfter][1] - dng->mapDiv[divAfter][3]) count = RL_COUNT_X;
		else count = RL_COUNT_Y;

		if (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2] < dng->divCountRand * 2 + 8) {
			size_t k = 0;
			for (size_t j = 1; j < dng->mapDivCount; ++j) {
				if (dng->mapDiv[j][0] - dng->mapDiv[j][2] > k) {
					k = dng->mapDiv[j][0] - dng->mapDiv[j][2];
					divAfter = j;
					count = RL_COUNT_X;
				}
				if (dng->mapDiv[j][1] - dng->mapDiv[j][3] > k) {
					k = dng->mapDiv[j][1] - dng->mapDiv[j][3];
					divAfter = j;
					count = RL_COUNT_Y;
				}
			}
		}

		dng->mapRoad[i][0] = divAfter;
		dng->mapRoad[i][1] = count;

		for (size_t j = 1; j < i; ++j)
			if (dng->mapRoad[j][0] == divAfter) dng->mapRoad[j][0] = i;

		//count���̐ݒ�
		dng->mapDiv[i][count] = dng->mapDiv[divAfter][count + 2] + (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3 + (size_t)GetRand((int)((dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3)); //0.���̉E�[(iR)�̍��W(divAfter*R/3~2divAfter*R/3)
		dng->mapDiv[i][count + 2] = dng->mapDiv[divAfter][count + 2]; //0.���̍��[(iL)�̍��W(divAfterL)
		dng->mapDiv[divAfter][count + 2] = dng->mapDiv[i][count]; //divAfter���̍��[(divAfterL)�̍��W(iR)

		//count�Ƃ͋t�̎��̐ݒ�
		dng->mapDiv[i][abs(count - 1)] = dng->mapDiv[divAfter][abs(count - 1)]; //���̉E�[(iR)�̍��W(divAfterR)
		dng->mapDiv[i][abs(count - 1) + 2] = dng->mapDiv[divAfter][abs(count - 1) + 2]; //���̍��[(iL)�̍��W(divAfterL)
	}
	
	/*�����𐶐����鏈��*/
	for (size_t i = 0; i < dng->mapDivCount; ++i) {//�敪��
		//dng->mapRoomPlayer[i] = 0;//�v���C���[�N��������
		dng->mapRoom[i][2] = dng->mapDiv[i][2]; //�敪��X�n�_���}�b�vX�n�_�֑��
		dng->mapRoom[i][3] = dng->mapDiv[i][3]; //�敪��Y�n�_���}�b�vY�n�_�֑��

		//X���W�̕����̒������w��
		//dng->mapRoom[i][0] = dng->mapDiv[i][2] + dng->divCountRand + (size_t)GetRand((int)dng->roomLengthRandX);
		dng->mapRoom[i][0] = dng->mapDiv[i][2] + dng->roomLengthMinX + (size_t)GetRand((int)dng->roomLengthRandX);
		if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
			dng->mapRoom[i][0] = dng->mapDiv[i][0] - 4;
			if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
				dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			}
		}

		dng->mapRoom[i][1] = dng->mapDiv[i][3] + dng->roomLengthMinY + (size_t)GetRand((int)dng->roomLengthRandY);
		if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
			dng->mapRoom[i][1] = dng->mapDiv[i][1] - 4;
			if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
				dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
			}
		}

		if (dng->mapRoom[i][0] - dng->mapDiv[i][2] <= 1 || dng->mapRoom[i][1] - dng->mapDiv[i][3] <= 1) {
			dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
		}
		size_t l = (size_t)GetRand((int)(dng->mapDiv[i][0] - dng->mapRoom[i][0] - 5)) + 2;
		size_t m = (size_t)GetRand((int)(dng->mapDiv[i][1] - dng->mapRoom[i][1] - 5)) + 2;
		dng->mapRoom[i][0] += l;
		dng->mapRoom[i][2] += l;
		dng->mapRoom[i][1] += m;
		dng->mapRoom[i][3] += m;

		for (size_t j = dng->mapRoom[i][2]; j < dng->mapRoom[i][0]; ++j) {
			for (size_t k = dng->mapRoom[i][3]; k < dng->mapRoom[i][1]; ++k) {
				maprl[j][k].mapData = i + 20;
				dng->count[i]++;
			}
		}
	}

	/*�ʘH�𐶐����鏈��*/
	/*�ʘH�͂Q�����Ԃׂ̍����̂��Ƃ��w���B
	�ʘH����邽�߂ɂQ���������ꂼ��O(Before)�ƌ�(After)�ŕ�����B
	for���őS�Ă̕������`�F�b�N���A�O��̕������q���ʘH�����B
	�܂��A�O�̒ʘH�����A���Ɍ�̒ʘH�����B
	�Ō�ɑO�ƌ�̒ʘH���q����B
	*/
	size_t roomAfter;
	for (size_t roomBefore = 0; roomBefore < dng->mapDivCount; ++roomBefore) {
		roomAfter = dng->mapRoad[roomBefore][0];

		//X���W�̒ʘH
		switch (dng->mapRoad[roomBefore][1]) {
		case RL_COUNT_X:
			dng->mapRoad[roomBefore][2] = (size_t)GetRand((int)(dng->mapRoom[roomBefore][1] - dng->mapRoom[roomBefore][3] - 2)); //�O���̒ʘH�̈ʒu
			dng->mapRoad[roomBefore][3] = (size_t)GetRand((int)(dng->mapRoom[roomAfter][1] - dng->mapRoom[roomAfter][3] - 2)); //�㑤�̒ʘH�̈ʒu
																																	 //�O�̒ʘH
			for (size_t j = dng->mapRoom[roomBefore][0]; j < dng->mapDiv[roomBefore][0]; ++j)
				maprl[j][dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

			//��̒ʘH
			for (size_t j = dng->mapDiv[roomAfter][2]; j < dng->mapRoom[roomAfter][2]; ++j)
				maprl[j][dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

			//�ʘH���Ȃ�
			for (size_t j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; ++j)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ��� 2����5(�ォ�牺)
			for (size_t j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; ++j)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ��� 5����2(�������)
			break;

		case RL_COUNT_Y:
			dng->mapRoad[roomBefore][2] = (size_t)GetRand((int)(dng->mapRoom[roomBefore][0] - dng->mapRoom[roomBefore][2] - 2)); //�O���̒ʘH�̈ʒu
			dng->mapRoad[roomBefore][3] = (size_t)GetRand((int)(dng->mapRoom[roomAfter][0] - dng->mapRoom[roomAfter][2] - 2)); //�㑤�̒ʘH�̈ʒu
																																	 //�O�̒ʘH
			for (size_t j = dng->mapRoom[roomBefore][1]; j < dng->mapDiv[roomBefore][1]; ++j)
				maprl[dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

			//��̒ʘH
			for (size_t j = dng->mapDiv[roomAfter][3]; j < dng->mapRoom[roomAfter][3]; ++j)
				maprl[dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

			//�ʘH���Ȃ�
			for (size_t j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; ++j)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���
			for (size_t j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; ++j)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���
			break;
		}

	}

	return 0;
}

MapData::MapData()
	:maprl(MAPY_RLk, vector<RogueLikeMap>(MAPX_RLk, 0)),
	transparentMap(MAPY_RLk, vector<int>(MAPX_RLk, 0)){

	sx = sy = gx = gy = 0;
	//��ŁA���̊K�ֈړ������Ƃ��������Z����悤�ɂ���
	stageNum++;
	//

	minDestination = -1;
	while (minDestination == -1) {
		//�_���W��������
		while (rogueLikeMapMake(&dng, maprl));
		Decide_Pos();
		//�X�^�[�g����S�[���܂łȂ����Ă��邩�`�F�b�N���āA�ŒZ�������L�^���Ă���
		minDestination = BreadthFirstSearch();
	}
	for (size_t y = 0; y < MAPY_RLk; y++) {
		for (size_t x = 0; x < MAPX_RLk; x++) {
			transparentMap[y][x] = maprl[y][x].mapData;
		}
	}

	if (mapchip[0] == 0) LoadDivGraph("Images\\mapchip.png", 3, 3, 1, 32, 32, mapchip);
}

void MapData::draw(int x, int y) {
	int px = x / CHIPSIZE;
	int py = y / CHIPSIZE;
	minx = x / CHIPSIZE - DRAW_CHIPNUM_X >= 0 ? x / CHIPSIZE - DRAW_CHIPNUM_X : 0;
	miny = y / CHIPSIZE - DRAW_CHIPNUM_Y >= 0 ? y / CHIPSIZE - DRAW_CHIPNUM_Y : 0;
	maxx = (size_t)x / CHIPSIZE + DRAW_CHIPNUM_X < MAPX_RLk ? x / CHIPSIZE + DRAW_CHIPNUM_X : MAPX_RLk - 1;
	maxy = (size_t)y / CHIPSIZE + DRAW_CHIPNUM_Y < MAPY_RLk ? y / CHIPSIZE + DRAW_CHIPNUM_Y : MAPY_RLk - 1;
	addx = 0, addy = 0;
	if (minx == 0) addx = x / CHIPSIZE - DRAW_CHIPNUM_X;
	if (miny == 0) addy = y / CHIPSIZE - DRAW_CHIPNUM_Y;
	if (maxx == MAPX_RLk) addx = -1 * (x / CHIPSIZE - MAPX_RLk + DRAW_CHIPNUM_X);
	if (maxy == MAPY_RLk) addy = -1 * (y / CHIPSIZE - MAPY_RLk + DRAW_CHIPNUM_Y);
	for (size_t i = miny; i < maxy; ++i) {
		for (size_t j = minx; j < maxx; ++j) {
			size_t kind = 0;
			if (i == gy && j == gx) kind = GOAL;
			else kind = maprl[i][j].mapData;
			int posy = i - miny - addy;
			int posx = j - minx - addx;
			int drawx = DRAW_STARTPOS_X + posx * CHIPSIZE;
			int drawy = DRAW_STARTPOS_Y + posy * CHIPSIZE;
			//�����̕`��
			if (kind >= 20) DrawGraph(drawx, drawy, mapchip[1], TRUE);
			else {
				switch (kind) {
				case WALL: DrawGraph(drawx, drawy, mapchip[0], TRUE); break;
				case PATH: DrawGraph(drawx, drawy, mapchip[1], TRUE); break;
				case GOAL: DrawGraph(drawx, drawy, mapchip[2], TRUE); break;
				}
			}
			if (kind != WALL) {
				if (dirbox != -1) {
					DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 255, 255), FALSE);
				}
				switch (dirbox) {
				case 0: /*�����*/if (px == j && py > i) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				case 1: /*������*/if (px == j && py < i) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				case 2: /*�E����*/if (px < j && py == i) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				case 3: /*������*/if (px > j && py == i) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				case 4: /*�E�����*/if (j - px == py - i && j > px) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				case 5: /*�E������*/if (j - px == i - py && j > px) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				case 6: /*�������*/if (j - px == i - py && j < px) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				case 7: /*��������*/if (j - px == py - i && j < px) DrawBox(drawx, drawy, drawx + CHIPSIZE, drawy + CHIPSIZE, GetColor(255, 0, 0), FALSE); break;
				default: break;
				}
			}
		}
	}
	dirbox = -1;
}

void MapData::DrawTransparentMaze(int x, int y) {
	//�v���C���[�����łɒʂ����ꏊ���`�F�b�N����
	int room = -1;
	if (transparentMap[y][x] >= 20) room = transparentMap[y][x];
	else transparentMap[y][x] = 10;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	for (size_t y = 0; y < MAPY_RLk; y++) {
		for (size_t x = 0; x < MAPX_RLk; x++) {
			if (transparentMap[y][x] == 10 || transparentMap[y][x] == -1) DrawBox(x * 5, y * 5, x * 5 + 5, y * 5 + 5, GetColor(0, 0, 255), TRUE);
			if (transparentMap[y][x] == room) transparentMap[y][x] = -1;
		}
	}
	DrawBox(x * 5, y * 5, x * 5 + 5, y * 5 + 5, GetColor(255, 255, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MapData::DrawDarkness(int x, int y) {
	SetDrawBlendMode(DX_BLENDMODE_MUL, 50);
	DrawBox(96, 48, 544, 432, GetColor(100, 100, 100), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
	for (size_t i = miny; i < maxy; i++) {
		for (size_t j = minx; j < maxx; j++) {
			size_t kind = maprl[i][j].mapData;
			int posy = i - miny - addy;
			int posx = j - minx - addx;
			int tx = DRAW_STARTPOS_X + posx * CHIPSIZE;
			int ty = DRAW_STARTPOS_Y + posy * CHIPSIZE;
			if (kind == maprl[y][x].mapData) {
				if (kind >= 20) { DrawBox(tx, ty, tx + 32, ty + 32, GetColor(200, 200, 200), TRUE); lightknd = 1; }
				else if (kind == PATH || (kind >= 20 && dng.count[kind - 20] == 1)) lightknd = 2;
				else lightknd = 0;
			}
		}
	}
	if(lightknd == 2) DrawCircle(PLAYER_POS_X + 16, PLAYER_POS_Y + 16, CHIPSIZE + 16, GetColor(200, 200, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MapData::DrawEnemyPos(int x, int y) {
	DrawBox(x * 5, y * 5, x * 5 + 5, y * 5 + 5, GetColor(255, 0, 0), TRUE);
}

void MapData::DrawTempMap() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	for (size_t y = 0; y < MAPY_RLk; y++) {
		for (size_t x = 0; x < MAPX_RLk; x++) {
			size_t kind = maprl[y][x].mapData;
			switch (kind) {
			case WALL: DrawBox(x * 5, y * 5, x * 5 + 5, y * 5 + 5, GetColor(255, 255, 0), TRUE); break;
			case START:DrawBox(x * 5, y * 5, x * 5 + 5, y * 5 + 5, GetColor(0, 0, 0), TRUE); break;
			case GOAL: DrawBox(x * 5, y * 5, x * 5 + 5, y * 5 + 5, GetColor(255, 0, 0), TRUE); break;
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�������牺�A���T��

typedef pair<int, int> point_t;

point_t operator+(const point_t& lhs, const point_t& rhs)
{
	point_t p = { lhs.first + rhs.first, lhs.second + rhs.second };
	return p;
}

bool operator==(const point_t& lhs, const point_t& rhs)
{
	return (lhs.first == rhs.first) && (lhs.second == rhs.second);
}

bool is_in_field(int col, int row, const point_t& point)
{
	const int c = point.second;
	const int r = point.first;
	return (0 <= c && c < col) && (0 <= r && r < row);
}

int MapData::BreadthFirstSearch() {
	// 2. �e�}�X�̖K�◚��(memo)���쐬����
   //    memo�ɂ̓X�^�[�g���炻�̃}�X�܂ł̕������i�[����(�����l��0)
	vector<vector<int>> memo;
	for (size_t i = 0; i < MAPY_RLk; ++i) {
		vector<int> v(MAPX_RLk, 0);
		memo.push_back(v);
	}

	// �ړ�����(�㉺���E)
	const point_t points[] = {
		{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 },
	};

	// 3. �X�^�[�g�̃}�X���L���[�Ɋi�[����
	const point_t s(sy, sx);
	const point_t g(gy, gx);
	queue<point_t> q;
	q.push(s);

	// 11. 4����10���L���[����ɂȂ�܂ŌJ��Ԃ�
	while (!q.empty()) {
		// 4. �L���[�̐擪�����}�X�擾����
		point_t cur = q.front(); q.pop();

		// 5. ���o�����}�X���S�[���Ȃ�I��
		if (cur == g) {
			return memo[cur.first][cur.second];
		}

		for (const auto& point : points) {
			// 6. �菇4�Ŏ��o�����}�X(cur)����㉺���E�̉��ꂩ�Ɉړ�����
			point_t next = cur + point;
			// 7. �ړ���̃}�X(next)�����H�O�łȂ����Ƃ��m�F����(���H�O�̏ꍇ�͎菇6�ɖ߂�)
			if (is_in_field(MAPX_RLk, MAPY_RLk, next)) {
				const int s = maprl[next.first][next.second].mapData;
				// 8. �ړ���̃}�X(next)�����܂��̓S�[���ł��邱�Ƃ��m�F����(���ł��S�[���ł��Ȃ��ꍇ�͎菇6�ɖ߂�)
				if (s == 0 || s == 3 || s >= 20) {
					// 9. �ړ���̃}�X(next)�����K��ł��邱�Ƃ��m�F����(�K��ς݂̏ꍇ�͎菇6�ɖ߂�)
					if (memo[next.first][next.second] == 0) {
						// 10. �ړ���̃}�X(next)���L���[�Ɋi�[���A�K�◚�����X�V����
						q.push(next);
						memo[next.first][next.second] = memo[cur.first][cur.second] + 1;
					}
				}
			}
		}
	}
	return -1;
}

void MapData::Decide_Pos() {
	//��ŁA�����̗�����ς���
	chickNum = GetRand(2) + 1;
	vector<int> tempchick(chickNum, 0);
	cx = cy = tempchick;
	//cy = tempchick;
	//��ŁA�����̗�����ς���(�G�̓t�@�C��������𓾂�)
	enemyNum = GetRand(2) + 2;
	//enemyNum = 1;
	vector<int> tempenemy(enemyNum, 0);
	ex = ey = tempenemy;
	while (sx == gx && sy == gy) {
		int s_divcount = GetRand(dng.mapDivCount - 1);
		while (dng.count[s_divcount] == 1) s_divcount = GetRand(dng.mapDivCount - 1);
		int temp_sy = GetRandomNum(dng.mapRoom[s_divcount][2], dng.mapRoom[s_divcount][0]);
		int temp_sx = GetRandomNum(dng.mapRoom[s_divcount][3], dng.mapRoom[s_divcount][1]);
		int g_divcount = GetRand(dng.mapDivCount - 1);
		while (dng.count[g_divcount] == 1) g_divcount = GetRand(dng.mapDivCount - 1);
		int temp_gy = GetRandomNum(dng.mapRoom[g_divcount][2], dng.mapRoom[g_divcount][0]);
		int temp_gx = GetRandomNum(dng.mapRoom[g_divcount][3], dng.mapRoom[g_divcount][1]);
		sx = temp_sx;
		sy = temp_sy;
		gx = temp_gx;
		gy = temp_gy;
	}
	for (int i = 0; i < chickNum; i++) {
		while (sx == cx[i] || gx == cx[i] || sy == cy[i] || gy == cy[i] || cx[i] == 0 || cy[i] == 0) {
			int c_divcount = GetRand(dng.mapDivCount - 1);
			while (dng.count[c_divcount] == 1) c_divcount = GetRand(dng.mapDivCount - 1);
			int temp_cy = GetRandomNum(dng.mapRoom[c_divcount][2], dng.mapRoom[c_divcount][0]);
			int temp_cx = GetRandomNum(dng.mapRoom[c_divcount][3], dng.mapRoom[c_divcount][1]);
			cx[i] = temp_cx;
			cy[i] = temp_cy;
		}
	}
	for (int i = 0; i < enemyNum; i++) {
		int e_divcount = GetRand(dng.mapDivCount - 1);
		while (dng.count[e_divcount] == 1) e_divcount = GetRand(dng.mapDivCount - 1);
		int temp_ey = GetRandomNum(dng.mapRoom[e_divcount][2], dng.mapRoom[e_divcount][0]);
		int temp_ex = GetRandomNum(dng.mapRoom[e_divcount][3], dng.mapRoom[e_divcount][1]);
		ex[i] = temp_ex;
		ey[i] = temp_ey;
	}
	maprl[sy][sx] = 2;
	for (int i = -3; i < 4; i++) {
		for (int j = -3; j < 4; j++) {
			if (maprl[sy][sx].mapData == 2) {
				if (maprl[sy + i][sx + j].mapData >= 20) maprl[sy][sx].mapData = maprl[sy + i][sx + j].mapData;
			}
			else {
				break;
			}
		}
	}
	maprl[gy][gx] = 3;
	for (int i = -3; i < 4; i++) {
		for (int j = -3; j < 4; j++) {
			if (maprl[gy][gx].mapData == 3) {
				if (maprl[gy + i][gx + j].mapData >= 20) maprl[gy][gx].mapData = maprl[gy + i][gx + j].mapData;
			}
			else {
				break;
			}
		}
	}
}

int MapData::mapchip[3];
int MapData::stageNum;