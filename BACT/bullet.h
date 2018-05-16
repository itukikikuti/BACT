#pragma once

#include <vector>
#include "position.h"
#include "graphic.h"
#include "sound.h"

#define target_enemy	(unsigned char)0
#define target_player	(unsigned char)1

enum BulletType{
	BULLET_TYPE_SHOT,
	BULLET_TYPE_LASER,
	BULLET_TYPE_GATLING,
	BULLET_TYPE_BAZOOKA,
	BULLET_TYPE_SABER,
	BULLET_TYPE_BARRIER,
	BULLET_TYPE_MISSILE,
	BULLET_TYPE_TYPHOON,
	BULLET_TYPE_BOMB,
	BULLET_TYPE_GAS,
	BULLET_TYPE_ENEMY,
	BULLET_TYPE_FIRE,
	BULLET_TYPE_BEAM,
	BULLET_TYPE_IMPACT,

	BULLET_TYPE_MAX,
};

class BulletData{
public:
	Graphic		image;				//’Êí‚Ì‰æ‘œ
	Graphic		dieImage;			//“–‚½‚Á‚½‚Ì‰æ‘œ
	Sound		sound;				//”­ËA“–‚½‚Á‚½‚ÌŒø‰Ê‰¹
	std::string	name;				//•Ší‚Ì–¼‘O
	std::string	caption;			//•Ší‚Ìà–¾
	int			ammoMax;			//’e–òÅ‘å”
	int			existTime;			//‘±ŠÔ
	int			dieTime;			//Á–ÅŠÔ
	float		power;				//’Êí‚ÌUŒ‚—Í
	float		diePower;			//Á–Å‚ÌUŒ‚—Í
	int			setNum;				//“¯”­Ë”
	int			resetWait;			//”­Ë‘Ò‚¿ŠÔ
	float		startRadius;		//‰Šú”¼Œa
	int			startRadiusRandom;	//‰Šú”¼Œa‚Ì‚Ô‚ê
	float		startSpeed;			//‰Šú‘¬“x
	int			startSpeedRandom;	//‰Šú‘¬“x‚Ì‚Ô‚ê
	float		startAngle;			//‰ŠúŠp“x
	int			startAngleRandom;	//‰ŠúŠp“x‚Ì‚Ô‚ê
	float		existRadiusChange;	//’Êí‚Ì”¼Œa‚Ì•Ï‰»
	float		existSpeedChange;	//’Êí‚Ì‘¬“x‚Ì•Ï‰»
	float		existAngleChange;	//’Êí‚ÌŠp“x‚Ì•Ï‰»
	float		endRadius;			//Á–Å”¼Œa
	int			endRadiusRandom;	//Á–Å”¼Œa‚Ì‚Ô‚ê
	float		endSpeed;			//Á–Å‘¬“x
	int			endSpeedRandom;		//Á–Å‘¬“x‚Ì‚Ô‚ê
	float		endAngle;			//Á–ÅŠp“x
	int			endAngleRandom;		//Á–ÅŠp“x‚Ì‚Ô‚ê
	float		dieRadiusChange;	//Á–Å‚Ì”¼Œa‚Ì•Ï‰»
	float		dieSpeedChange;		//Á–Å‚Ì‘¬“x‚Ì•Ï‰»
	float		dieAngleChange;		//Á–Å‚ÌŠp“x‚Ì•Ï‰»
};

class Bullet{
public:
	BulletType type;
	Position2D pos;
	float radius;
	float speed;
	double angle;
	unsigned char target;
	int frame;
	Bullet();
	Bullet(BulletType type, int x, int y, double angle,unsigned char target = target_enemy);
	~Bullet();
	void Set(BulletType type, int x, int y, double angle, unsigned char target = target_enemy);
	void Move();
	bool Delete(int bulletId);
	void CheckHit();
	void Draw();
};

class EnemyBullet : public Bullet
{
	EnemyBullet();
	EnemyBullet(BulletType type, int x, int y, double angle);
	~EnemyBullet();
};

extern BulletData bulletData[BULLET_TYPE_MAX];
extern std::vector<Bullet> bullet;

extern void LoadBulletData();
extern void SetBullet(BulletType type, int x, int y, double angle, unsigned char target = target_enemy);