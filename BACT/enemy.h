#pragma once

#include <vector>
#include <string>
#include "position.h"
#include "bullet.h"

enum EnemyType{
	ENEMY_TYPE_PATROL,
	ENEMY_TYPE_SPIKE,
	ENEMY_TYPE_BOMB,
	ENEMY_TYPE_SHOT,
	ENEMY_TYPE_SNIPER,
	ENEMY_TYPE_LASER,
	ENEMY_TYPE_VENOM,
	ENEMY_TYPE_TELEPORT,
	ENEMY_TYPE_HOMING,
	ENEMY_TYPE_BOSS_SPEED,
	ENEMY_TYPE_BOSS_BIG,
	ENEMY_TYPE_BOSS_CENTIPEDE,
	ENEMY_TYPE_BOSS_MOTH,
	ENEMY_TYPE_BOSS_SAMURAI,
	ENEMY_TYPE_BOSS_DRAGON,
	ENEMY_TYPE_BOSS_BIG_SNAKE,
	ENEMY_TYPE_PARTS_BIG_LEG,
	ENEMY_TYPE_PARTS_CENTIPEDE_BODY,
	ENEMY_TYPE_PARTS_MOTH_TAIL,
	ENEMY_TYPE_PARTS_SAMURAI_HAND,
	ENEMY_TYPE_PARTS_DRAGON_WING,
	ENEMY_TYPE_PARTS_DRAGON_BODY,
	ENEMY_TYPE_PARTS_BIG_SNAKE_CLAW,
	ENEMY_TYPE_PARTS_BIG_SNAKE_HEAD,

	ENEMY_TYPE_MAX,
};

class EnemyData{
public:
	std::string name;
	int radius;
	int lifeMax;
};

class Enemy{
public:
	EnemyType type;
	Position2D pos;
	double angle;
	int life;
	int frame;
	Enemy();
	Enemy(EnemyType type, int x, int y);
	~Enemy();
	void Set(EnemyType type, int x, int y);
	void Move(int enemyId);					//ìÆÇ©ÇµÇΩÇËíeÇî≠éÀÇµÇΩÇËÇ∑ÇÈ
	void Shoot(BulletType type);			//ìGÇÃéÌóﬁÇ…ÇÊÇ¡ÇƒèoÇ∑íeÇïœÇ¶ÇÈ
	bool Delete(int enemyId);
	void CheckHit();
	void Draw();
};

extern EnemyData enemyData[ENEMY_TYPE_MAX];
extern std::vector<Enemy> enemy;

extern void LoadEnemyData();
extern void SetEnemy(EnemyType type, int x, int y);
extern void DeleteAllEnemy();
extern void SetEnemyBoss(EnemyType type);
