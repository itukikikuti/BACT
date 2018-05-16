#pragma once

#include <string>
#include "enemy.h"

class Stage{
public:
	std::string name;
	std::string backImageFilePath;
	int backGroundScrollSpeed;
	EnemyType bossType;
	int bossSetFrame;
};

extern Stage stage[7];

extern void LoadStageData();
