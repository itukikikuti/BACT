#include "DxLib.h"
#include "stage.h"
#include "main.h"

Stage stage[7];

void LoadStageData()
{
	for (int i = 0; i < 7; i++)
	{
		char tempString[256];
		LoadCSV(tempString, "data/parameter/stage.csv", i + 1, 0, 7, 5);
		stage[i].name = tempString;
		LoadCSV(tempString, "data/parameter/stage.csv", i + 1, 1, 7, 5);
		stage[i].backImageFilePath = tempString;
		LoadCSV(tempString, "data/parameter/stage.csv", i + 1, 2, 7, 5);
		stage[i].backGroundScrollSpeed = atoi(tempString);
		LoadCSV(tempString, "data/parameter/stage.csv", i + 1, 3, 7, 5);
		stage[i].bossType = (EnemyType)atoi(tempString);
		LoadCSV(tempString, "data/parameter/stage.csv", i + 1, 4, 7, 5);
		stage[i].bossSetFrame = atoi(tempString);
	}
}
