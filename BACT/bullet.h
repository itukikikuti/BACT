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
	Graphic		image;				//通常の画像
	Graphic		dieImage;			//当たった時の画像
	Sound		sound;				//発射、当たった時の効果音
	std::string	name;				//武器の名前
	std::string	caption;			//武器の説明
	int			ammoMax;			//弾薬最大数
	int			existTime;			//持続時間
	int			dieTime;			//消滅時間
	float		power;				//通常の攻撃力
	float		diePower;			//消滅時の攻撃力
	int			setNum;				//同時発射数
	int			resetWait;			//発射待ち時間
	float		startRadius;		//初期半径
	int			startRadiusRandom;	//初期半径のぶれ
	float		startSpeed;			//初期速度
	int			startSpeedRandom;	//初期速度のぶれ
	float		startAngle;			//初期角度
	int			startAngleRandom;	//初期角度のぶれ
	float		existRadiusChange;	//通常時の半径の変化
	float		existSpeedChange;	//通常時の速度の変化
	float		existAngleChange;	//通常時の角度の変化
	float		endRadius;			//消滅時半径
	int			endRadiusRandom;	//消滅時半径のぶれ
	float		endSpeed;			//消滅時速度
	int			endSpeedRandom;		//消滅時速度のぶれ
	float		endAngle;			//消滅時角度
	int			endAngleRandom;		//消滅時角度のぶれ
	float		dieRadiusChange;	//消滅時の半径の変化
	float		dieSpeedChange;		//消滅時の速度の変化
	float		dieAngleChange;		//消滅時の角度の変化
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