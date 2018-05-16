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
	BulletType holdWeapon;				//‚Á‚Ä‚¢‚é•Ší
	bool bulletFlag[BULLET_TYPE_MAX];	//•Ší‚ÌŠ
	int bulletWait[BULLET_TYPE_MAX];	//•Ší‚Ì”­Ë‘ÒƒtƒŒ[ƒ€
	int bulletLevel[BULLET_TYPE_MAX];	//•Ší‚ÌƒŒƒxƒ‹
	int bulletAmmo[BULLET_TYPE_MAX];	//•Ší‚Ì’e”
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