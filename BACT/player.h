#pragma once

#include "position.h"
#include "bullet.h"

class Player{
public:
	int type;
	Position2D pos;
	int speed;
	int life;
	int lifeMax;
	BulletType holdWeapon;				//�����Ă��镐��
	bool bulletFlag[BULLET_TYPE_MAX];	//����̏���
	int bulletWait[BULLET_TYPE_MAX];	//����̔��ˑ҃t���[��
	int bulletLevel[BULLET_TYPE_MAX];	//����̃��x��
	int bulletAmmo[BULLET_TYPE_MAX];	//����̒e��
	Player();
	Player(int x, int y);
	~Player();
	void Set(int x, int y);
	void Move();
	void Shoot();
	void Eat();
	void Draw();
};

extern Player player;