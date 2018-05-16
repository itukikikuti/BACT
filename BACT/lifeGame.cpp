#include "DxLib.h"
#include "main.h"
#include "lifeGame.h"

#define LIFE_GAME_CELL_X 256
#define LIFE_GAME_CELL_Y 192

bool lifeGameCell[LIFE_GAME_CELL_Y][LIFE_GAME_CELL_X] = { 0 };

void ResetLifeGame(float setRate)
{
	//�����_���ɐ������Z�����o��
	for (int y = 0; y < LIFE_GAME_CELL_Y; y++)
	{
		for (int x = 0; x < LIFE_GAME_CELL_X; x++)
		{
			//(setRate*100)%�̊m����true�ɂ���
			if (GetRand(99) <= (setRate * 100))lifeGameCell[y][x] = true;
		}
	}
}
void UpdateLifeGame()
{
	bool nextCell[LIFE_GAME_CELL_Y][LIFE_GAME_CELL_X];

	//lifeGameCell�𕡐�����
	for (int y = 0; y < LIFE_GAME_CELL_Y; y++)
	{
		for (int x = 0; x < LIFE_GAME_CELL_X; x++)
		{
			nextCell[y][x] = lifeGameCell[y][x];
		}
	}

	//��������
	for (int y = 0; y < LIFE_GAME_CELL_Y; y++)
	{
		for (int x = 0; x < LIFE_GAME_CELL_X; x++)
		{
			int trueNum = 0;
			//�����true�̐��𒲂ׂ�
			for (int y2 = y - 1; y2 < y + 2; y2++)
			{
				for (int x2 = x - 1; x2 < x + 2; x2++)
				{
					if (x == x2&&y == y2)continue;//�����͒��ׂȂ�
					//�z�񂩂�͂ݏo���Ă��Ȃ����`�F�b�N����
					if (x2 >= 0 &&
						x2 < LIFE_GAME_CELL_X &&
						y2 >= 0 &&
						y2 < LIFE_GAME_CELL_Y)
					{
						//true��������J�E���g����
						if (lifeGameCell[y2][x2] == true)trueNum++;
					}
				}
			}
			if ((lifeGameCell[y][x] == true &&
				trueNum == 2) ||
				(lifeGameCell[y][x] == true &&
				trueNum == 3) ||
				(lifeGameCell[y][x] == false &&
				trueNum == 3))
			{
				nextCell[y][x] = true;
			}
			else
			{
				nextCell[y][x] = false;
			}
		}
	}

	//nextCell��lifeGameCell�ɑ������
	for (int y = 0; y < LIFE_GAME_CELL_Y; y++)
	{
		for (int x = 0; x < LIFE_GAME_CELL_X; x++)
		{
			lifeGameCell[y][x] = nextCell[y][x];
		}
	}
}
void DrawLifeGame(const int updateTiming, int color)
{
	const int cellWidth = SCREEN_X / LIFE_GAME_CELL_X;	//�Z���̃T�C�Y
	const int cellHeight = SCREEN_Y / LIFE_GAME_CELL_Y;	//�Z���̃T�C�Y
	static int updateTimingCounter = 0;					//

	if (updateTimingCounter == 0)UpdateLifeGame();

	if (updateTimingCounter > 0)updateTimingCounter--;
	else updateTimingCounter = updateTiming;
	
	for (int y = 0; y < LIFE_GAME_CELL_Y; y++)
	{
		for (int x = 0; x < LIFE_GAME_CELL_X; x++)
		{
			if (lifeGameCell[y][x] == true)
			{
				DrawBox(x * cellWidth, y * cellHeight, (x + 1) * cellWidth, (y + 1) * cellHeight, color, true);
			}
		}
	}
}