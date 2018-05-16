#include "DxLib.h"
#include <string>
#include <math.h>
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

BulletData bulletData[BULLET_TYPE_MAX];
std::vector<Bullet> bullet;

void LoadBulletData()
{
	char tempString[256];
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 0, BULLET_TYPE_MAX, 31);
		bulletData[i].image.Load(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 1, BULLET_TYPE_MAX, 31);
		bulletData[i].dieImage.Load(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 2, BULLET_TYPE_MAX, 31);
		bulletData[i].sound.Load(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 3, BULLET_TYPE_MAX, 31);
		bulletData[i].name = tempString;
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 4, BULLET_TYPE_MAX, 31);
		bulletData[i].caption = tempString;
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 5, BULLET_TYPE_MAX, 31);
		bulletData[i].caption += "\n";
		bulletData[i].caption += tempString;
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 6, BULLET_TYPE_MAX, 31);
		bulletData[i].ammoMax = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 7, BULLET_TYPE_MAX, 31);
		bulletData[i].existTime = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 8, BULLET_TYPE_MAX, 31);
		bulletData[i].dieTime = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 9, BULLET_TYPE_MAX, 31);
		bulletData[i].power = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 10, BULLET_TYPE_MAX, 31);
		bulletData[i].diePower = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 11, BULLET_TYPE_MAX, 31);
		bulletData[i].setNum = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 12, BULLET_TYPE_MAX, 31);
		bulletData[i].resetWait = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 13, BULLET_TYPE_MAX, 31);
		bulletData[i].startRadius = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 14, BULLET_TYPE_MAX, 31);
		bulletData[i].startRadiusRandom = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 15, BULLET_TYPE_MAX, 31);
		bulletData[i].startSpeed = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 16, BULLET_TYPE_MAX, 31);
		bulletData[i].startSpeedRandom = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 17, BULLET_TYPE_MAX, 31);
		bulletData[i].startAngle = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 18, BULLET_TYPE_MAX, 31);
		bulletData[i].startAngleRandom = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 19, BULLET_TYPE_MAX, 31);
		bulletData[i].existRadiusChange = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 20, BULLET_TYPE_MAX, 31);
		bulletData[i].existSpeedChange = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 21, BULLET_TYPE_MAX, 31);
		bulletData[i].existAngleChange = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 22, BULLET_TYPE_MAX, 31);
		bulletData[i].endRadius = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 23, BULLET_TYPE_MAX, 31);
		bulletData[i].endRadiusRandom = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 24, BULLET_TYPE_MAX, 31);
		bulletData[i].endSpeed = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 25, BULLET_TYPE_MAX, 31);
		bulletData[i].endSpeedRandom = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 26, BULLET_TYPE_MAX, 31);
		bulletData[i].endAngle = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 27, BULLET_TYPE_MAX, 31);
		bulletData[i].endAngleRandom = atoi(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 28, BULLET_TYPE_MAX, 31);
		bulletData[i].dieRadiusChange = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 29, BULLET_TYPE_MAX, 31);
		bulletData[i].dieSpeedChange = atof(tempString);
		LoadCSV(tempString, "data/parameter/bullet.csv", i + 1, 30, BULLET_TYPE_MAX, 31);
		bulletData[i].dieAngleChange = atof(tempString);
		DrawLoad();
	}
}

Bullet::Bullet()
{
	Bullet::type = BULLET_TYPE_SHOT;
	Bullet::pos = Position2D(0, 0);
	Bullet::radius = 0;
	Bullet::speed = 0;
	Bullet::angle = 0;
	Bullet::frame = 0;
}
Bullet::Bullet(BulletType type, int x, int y, double angle, unsigned char target)
{
	Bullet::type = type;
	Bullet::pos = Position2D(x, y);
	Bullet::radius = bulletData[Bullet::type].startRadius + (GetRand(bulletData[Bullet::type].startRadiusRandom) - bulletData[Bullet::type].startRadiusRandom / 2);
	Bullet::speed = bulletData[Bullet::type].startSpeed + (GetRand(bulletData[Bullet::type].startSpeedRandom) - bulletData[Bullet::type].startSpeedRandom / 2);
	Bullet::angle = angle + GetRadian(bulletData[Bullet::type].startAngle) + GetRadian((GetRand(bulletData[Bullet::type].startAngleRandom) - bulletData[Bullet::type].startAngleRandom / 2));
	Bullet::target = target;
	Bullet::frame = 0;
}
Bullet::~Bullet()
{

}
void Bullet::Set(BulletType type, int x, int y, double angle, unsigned char target)
{
	Bullet::type = type;
	Bullet::pos = Position2D(x, y);
	Bullet::radius = bulletData[Bullet::type].startRadius + (GetRand(bulletData[Bullet::type].startRadiusRandom) - bulletData[Bullet::type].startRadiusRandom / 2);
	Bullet::speed = bulletData[Bullet::type].startSpeed + (GetRand(bulletData[Bullet::type].startSpeedRandom) - bulletData[Bullet::type].startSpeedRandom / 2);
	Bullet::angle = angle + GetRadian(bulletData[Bullet::type].startAngle) + GetRadian((GetRand(bulletData[Bullet::type].startAngleRandom) - bulletData[Bullet::type].startAngleRandom / 2));
	Bullet::target = target;
	Bullet::frame = 0;
}
//弾を動かします
void Bullet::Move()
{
	//弾が生きているか
	//消滅している最中かどうかによって
	//大きさ、角度、スピードを変える

	//弾が持続していたら
	if (Bullet::frame < bulletData[Bullet::type].existTime)
	{
		Bullet::radius += bulletData[Bullet::type].existRadiusChange;
		Bullet::speed += bulletData[Bullet::type].existSpeedChange;
		Bullet::angle += GetRadian(bulletData[Bullet::type].existAngleChange);
	}
	//弾が消滅したら
	if (Bullet::frame == bulletData[Bullet::type].existTime)
	{
		Bullet::radius = bulletData[Bullet::type].endRadius + (GetRand(bulletData[Bullet::type].endRadiusRandom) - bulletData[Bullet::type].endRadiusRandom / 2);
		Bullet::speed = bulletData[Bullet::type].endSpeed + (GetRand(bulletData[Bullet::type].endSpeedRandom) - bulletData[Bullet::type].endSpeedRandom / 2);
		Bullet::angle = angle + GetRadian(bulletData[Bullet::type].endAngle) + GetRadian((GetRand(bulletData[Bullet::type].endAngleRandom) - bulletData[Bullet::type].endAngleRandom / 2));
	}
	//弾が消滅していたら
	if (Bullet::frame >= bulletData[Bullet::type].existTime)
	{
		Bullet::radius += bulletData[Bullet::type].dieRadiusChange;
		Bullet::speed += bulletData[Bullet::type].dieSpeedChange;
		Bullet::angle += GetRadian(bulletData[Bullet::type].dieAngleChange);
	}

	//例外としてサーベルはプレイヤーに追従します
	if (Bullet::type == BULLET_TYPE_SABER)
	{
		Bullet::pos.x(player.pos.x());
		Bullet::pos.y(player.pos.y());
	}

	//例外としてバリアはプレイヤーに追従します
	if (Bullet::type == BULLET_TYPE_BARRIER)
	{
		Bullet::pos.x(player.pos.x());
		Bullet::pos.y(player.pos.y());
	}

	//例外としてミサイルは敵を追従します
	if (Bullet::type == BULLET_TYPE_MISSILE&&
		Bullet::frame % 10 == 0 &&
		Bullet::frame != 0 &&
		enemy.size() != 0)
	{
		int nearEnemyNum = -1;			//近い敵の番号
		int distance = 1000;			//距離を保存する変数
		for (int i = 0; i < enemy.size(); i++)
		{
			if (distance > CheckDistance(enemy[i].pos.x(), enemy[i].pos.y(), Bullet::pos.x(), Bullet::pos.y()))
			{
				distance = CheckDistance(enemy[i].pos.x(), enemy[i].pos.y(), Bullet::pos.x(), Bullet::pos.y());
				nearEnemyNum = i;
			}
		}
		//敵が100ピクセルの距離内にいた時に
		//1番近い敵に向かってホーミングする
		if (nearEnemyNum != -1)
		{
			Bullet::angle = atan2(enemy[nearEnemyNum].pos.y() - Bullet::pos.y(), enemy[nearEnemyNum].pos.x() - Bullet::pos.x());
		}
	}

	Bullet::pos.x(Bullet::pos.x() + cos(Bullet::angle) * Bullet::speed);
	Bullet::pos.y(Bullet::pos.y() + sin(Bullet::angle) * Bullet::speed);
}
bool Bullet::Delete(int bulletId)
{
	if (Bullet::frame > bulletData[Bullet::type].existTime + bulletData[Bullet::type].dieTime)
	{
		bullet.erase(bullet.begin() + bulletId);
		return true;
	}
	else
	{
		Bullet::frame++;
	}
	return false;
}
void Bullet::CheckHit()
{
	//ターゲットが敵で、敵が存在したら
	if (Bullet::target == target_enemy && enemy.size() != 0)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			if (enemy[i].pos.x() - 16 < Bullet::pos.x() + Bullet::radius &&
				Bullet::pos.x() - Bullet::radius < enemy[i].pos.x() + 16 &&
				enemy[i].pos.y() - 16 < Bullet::pos.y() + Bullet::radius &&
				Bullet::pos.y() - Bullet::radius < enemy[i].pos.y() + 16)
			{
				enemy[i].life -= bulletData[Bullet::type].power;
				if (Bullet::frame < bulletData[Bullet::type].existTime)
				{
					Bullet::frame = bulletData[Bullet::type].existTime - 1;
				}
			}
		}
	}
	//ターゲットがプレイヤーの場合
	if (Bullet::target == target_player)
	{
		if (player.pos.x() - 16 < Bullet::pos.x() + Bullet::radius &&
			Bullet::pos.x() - Bullet::radius < player.pos.x() + 16 &&
			player.pos.y() - 16 < Bullet::pos.y() + Bullet::radius &&
			Bullet::pos.y() - Bullet::radius < player.pos.y() + 16)
		{
			player.life -= bulletData[Bullet::type].power;
			if (Bullet::frame < bulletData[Bullet::type].existTime)
			{
				Bullet::frame = bulletData[Bullet::type].existTime - 1;
			}
		}
	}
}
void Bullet::Draw()
{
	//弾が持続していたら
	if (Bullet::frame < bulletData[Bullet::type].existTime)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 191);
		DrawRotaGraph(Bullet::pos.x(), Bullet::pos.y(), Bullet::radius * 2 / bulletData[Bullet::type].image.width(), Bullet::angle, bulletData[Bullet::type].image.handle(), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawRotaGraph(Bullet::pos.x(), Bullet::pos.y(), Bullet::radius * 2 / bulletData[Bullet::type].image.width(), Bullet::angle, bulletData[Bullet::type].image.handle(), true);
	}
	//弾が消滅していたら
	if (Bullet::frame >= bulletData[Bullet::type].existTime)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 191);
		DrawRotaGraph(Bullet::pos.x(), Bullet::pos.y(), Bullet::radius * 2 / bulletData[Bullet::type].dieImage.width(), Bullet::angle, bulletData[Bullet::type].dieImage.handle(), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawRotaGraph(Bullet::pos.x(), Bullet::pos.y(), Bullet::radius * 2 / bulletData[Bullet::type].dieImage.width(), Bullet::angle, bulletData[Bullet::type].dieImage.handle(), true);
	}

	//当たり判定の範囲を円で表示します
	//DrawCircle(Bullet::pos.x(), Bullet::pos.y(), Bullet::radius, GetColor(255, 0, 0), true, 2);
}
void SetBullet(BulletType type, int x, int y, double angle, unsigned char target)
{
	int l = player.bulletLevel[player.holdWeapon] / 1000 + 1;	//レベル

	for (int i = 0; i < bulletData[type].setNum * l; i++)
	{
		if (bullet.size() < 256)
		{
			bullet.push_back(Bullet(type, x, y, angle, target));
			bulletData[type].sound.Play(DX_PLAYTYPE_BACK);
		}
	}
}
