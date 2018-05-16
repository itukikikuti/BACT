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
	Graphic		image;				//�ʏ�̉摜
	Graphic		dieImage;			//�����������̉摜
	Sound		sound;				//���ˁA�����������̌��ʉ�
	std::string	name;				//����̖��O
	std::string	caption;			//����̐���
	int			ammoMax;			//�e��ő吔
	int			existTime;			//��������
	int			dieTime;			//���Ŏ���
	float		power;				//�ʏ�̍U����
	float		diePower;			//���Ŏ��̍U����
	int			setNum;				//�������ː�
	int			resetWait;			//���ˑ҂�����
	float		startRadius;		//�������a
	int			startRadiusRandom;	//�������a�̂Ԃ�
	float		startSpeed;			//�������x
	int			startSpeedRandom;	//�������x�̂Ԃ�
	float		startAngle;			//�����p�x
	int			startAngleRandom;	//�����p�x�̂Ԃ�
	float		existRadiusChange;	//�ʏ펞�̔��a�̕ω�
	float		existSpeedChange;	//�ʏ펞�̑��x�̕ω�
	float		existAngleChange;	//�ʏ펞�̊p�x�̕ω�
	float		endRadius;			//���Ŏ����a
	int			endRadiusRandom;	//���Ŏ����a�̂Ԃ�
	float		endSpeed;			//���Ŏ����x
	int			endSpeedRandom;		//���Ŏ����x�̂Ԃ�
	float		endAngle;			//���Ŏ��p�x
	int			endAngleRandom;		//���Ŏ��p�x�̂Ԃ�
	float		dieRadiusChange;	//���Ŏ��̔��a�̕ω�
	float		dieSpeedChange;		//���Ŏ��̑��x�̕ω�
	float		dieAngleChange;		//���Ŏ��̊p�x�̕ω�
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