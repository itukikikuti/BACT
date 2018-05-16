#include "DxLib.h"
#include <math.h>
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "effect.h"

EnemyData enemyData[ENEMY_TYPE_MAX];
std::vector<Enemy> enemy;

enum EnemyParts{
	ENEMY_PARTS_EYE,
	ENEMY_PARTS_BODY,
	ENEMY_PARTS_THORN,
	ENEMY_PARTS_WING,
};

void DrawEnemyParts(EnemyParts type, int x, int y, double angle, double radius)
{
	static Graphic eyeBall("data/img/enemy/eye/eyeBall.png");
	static Graphic luster("data/img/enemy/eye/luster.png");
	static Graphic pupil("data/img/enemy/eye/pupil.png");
	static Graphic body("data/img/enemy/body.png");
	static Graphic thorn("data/img/enemy/thorn.png");
	static Graphic wing("data/img/enemy/wing.png");

	switch (type)
	{
	case ENEMY_PARTS_EYE:
		DrawRotaGraph(x, y, radius / 32.0, 0, eyeBall.handle(), true);
		DrawRotaGraph(x + cos(angle) * (radius / 3.0), y + sin(angle) * (radius / 3.0), radius / 32.0, 0, pupil.handle(), true);
		DrawRotaGraph(x, y, radius / 32.0, 0, luster.handle(), true);
		break;
	case ENEMY_PARTS_BODY:
		DrawRotaGraph(x, y, radius / 32.0, 0, body.handle(), true);
		break;
	case ENEMY_PARTS_THORN:
		DrawRotaGraph2(x, y, 0, 64, radius / 128.0, angle, thorn.handle(), true);
		break;
	case ENEMY_PARTS_WING:
		DrawRotaGraph2(x, y, 0, 64, radius / 128.0, angle, wing.handle(), true);
		break;
	default:break;
	}
}

Enemy::Enemy()
{
	Enemy::type = ENEMY_TYPE_PATROL;
	Enemy::pos = Position2D(0, 0);
	Enemy::angle = GetRadian(GetRand(360));
	Enemy::life = enemyData[Enemy::type].lifeMax;
	Enemy::frame = 0;
}
Enemy::Enemy(EnemyType type, int x, int y)
{
	Enemy::type = type;
	Enemy::pos = Position2D(x, y);
	Enemy::angle = GetRadian(GetRand(360));
	Enemy::life = enemyData[type].lifeMax;
	Enemy::frame = 0;
}
Enemy::~Enemy()
{

}
void Enemy::Set(EnemyType type, int x, int y)
{
	Enemy::type = type;
	Enemy::pos = Position2D(x, y);
	Enemy::angle = GetRadian(GetRand(360));
	Enemy::life = 10;
	Enemy::frame = 0;
}
//動かしたり弾を発射したりする
void Enemy::Move(int enemyId)
{
	switch (Enemy::type)
	{
	case ENEMY_TYPE_PATROL:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 50)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 150)Enemy::angle = DX_PI;
			if (Enemy::frame == 200)Enemy::angle = DX_PI;
			if (Enemy::frame == 250)Enemy::angle = DX_PI;
			if (Enemy::frame == 300)Enemy::angle = 0;
			if (Enemy::frame == 350)Enemy::angle = 0;
			if (Enemy::frame == 400)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_SPIKE:
		if (true)
		{
			int sp = 2;
			if (Enemy::frame % 50 == 0)Enemy::angle = GetRadian(GetRand(360));
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_BOMB:
		if (true)
		{
			int sp = 2;
			//敵の進行方向(true=左下に動く,false=右下に動く)
			static bool directionOfTravel = Enemy::pos.x() > SCREEN_X / 2 ? true : false;
			//斜め下に動く
			if (directionOfTravel == false)Enemy::angle = GetRadian(45);
			if (directionOfTravel == true)Enemy::angle = GetRadian(135);
			//画面の下半分ならまっすぐ下に動く
			if (Enemy::pos.y() > SCREEN_Y / 2)
			{
				Enemy::angle = GetRadian(90);
			}
			//割と近くにプレイヤーが居るなら
			//速度を上げてプレイヤーを追いかける
			int distance = CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y());
			if (distance < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			//プレイヤの至近距離にいたら
			//爆発して自分も死ぬ
			if (distance < 100)
			{
				Enemy::life = 0;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_SHOT:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = GetRadian(90);
			if (Enemy::frame == 150)Enemy::angle = GetRadian(0);
			if (Enemy::frame == 200)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				static int shootCount = 0;
				if (shootCount > 100)
				{
					sp = 0;
					Enemy::pos.y(Enemy::pos.y() - 1);
					Enemy::Shoot(BULLET_TYPE_SHOT);
					if (shootCount > 300)shootCount = 0;
				}
				else
				{
					Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
					sp = 3;
				}
				shootCount++;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_SNIPER:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = GetRadian(90);
			if (Enemy::frame == 150)Enemy::angle = GetRadian(0);
			if (Enemy::frame == 200)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				static int shootCount = 0;
				if (shootCount > 100)
				{
					sp = 0;
					Enemy::pos.y(Enemy::pos.y() - 1);
					Enemy::Shoot(BULLET_TYPE_LASER);
					if (shootCount > 300)shootCount = 0;
				}
				else
				{
					Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
					sp = 3;
				}
				shootCount++;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_LASER:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = GetRadian(90);
			if (Enemy::frame == 150)Enemy::angle = GetRadian(0);
			if (Enemy::frame == 200)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				static int shootCount = 0;
				if (shootCount > 100)
				{
					sp = 0;
					Enemy::pos.y(Enemy::pos.y() - 1);
					Enemy::Shoot(BULLET_TYPE_BEAM);
					if (shootCount > 300)shootCount = 0;
				}
				else
				{
					Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
					sp = 3;
				}
				shootCount++;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_VENOM:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 50)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 150)Enemy::angle = DX_PI;
			if (Enemy::frame == 200)Enemy::angle = DX_PI;
			if (Enemy::frame == 250)Enemy::angle = DX_PI;
			if (Enemy::frame == 300)Enemy::angle = 0;
			if (Enemy::frame == 350)Enemy::angle = 0;
			if (Enemy::frame == 400)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_TELEPORT:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 50)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 150)Enemy::angle = DX_PI;
			if (Enemy::frame == 200)Enemy::angle = DX_PI;
			if (Enemy::frame == 250)Enemy::angle = DX_PI;
			if (Enemy::frame == 300)Enemy::angle = 0;
			if (Enemy::frame == 350)Enemy::angle = 0;
			if (Enemy::frame == 400)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_HOMING:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 50)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 150)Enemy::angle = DX_PI;
			if (Enemy::frame == 200)Enemy::angle = DX_PI;
			if (Enemy::frame == 250)Enemy::angle = DX_PI;
			if (Enemy::frame == 300)Enemy::angle = 0;
			if (Enemy::frame == 350)Enemy::angle = 0;
			if (Enemy::frame == 400)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_BOSS_SPEED:
		if (true)
		{
			int sp = 10;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 10)Enemy::angle = 0;
			if (Enemy::frame == 20)Enemy::angle = DX_PI;
			if (Enemy::frame == 30)Enemy::angle = DX_PI;
			if (Enemy::frame == 40)Enemy::angle = DX_PI;
			if (Enemy::frame == 50)Enemy::angle = DX_PI;
			if (Enemy::frame == 60)Enemy::angle = 0;
			if (Enemy::frame == 70)Enemy::angle = 0;
			if (Enemy::frame == 80)Enemy::angle = 0;
			if (Enemy::frame == 90)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 110)Enemy::angle = DX_PI;
			if (Enemy::frame == 120)Enemy::angle = DX_PI;
			if (Enemy::frame == 130)Enemy::angle = DX_PI;
			if (Enemy::frame == 140)Enemy::angle = 0;
			if (Enemy::frame == 150)Enemy::angle = 0;
			if (Enemy::frame >= 390 && Enemy::frame <= 600)
			{
				Enemy::angle = atan2(100.0 - Enemy::pos.y(), 400 - Enemy::pos.x());
			}
			else if (Enemy::frame > 150)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 5;
			}
			if (Enemy::frame == 600)Enemy::frame = 0;
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_BOSS_BIG:
		if (true)
		{
			const int sp = 3;
			Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp);
		}
		break;
	case ENEMY_TYPE_BOSS_CENTIPEDE:
		if (true)
		{
			const int sp = 3;
			static double targetAngle = 0;
			static double targetAngleAdd = GetRadian(3);
			targetAngle += targetAngleAdd;
			if (targetAngle > GetRadian(12))targetAngleAdd = GetRadian(-3);
			if (targetAngle < GetRadian(-12))targetAngleAdd = GetRadian(3);
			Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x()) + targetAngle;
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp);
		}
		break;
	case ENEMY_TYPE_BOSS_MOTH:
		if (true)
		{
			int sp = 0;
			static double angle = GetRadian(90);
			static double angleAdd = 0;
			if (Enemy::frame >= 0 && Enemy::frame < 600)
			{
				angle += angleAdd;
				angleAdd += 0.0001;
				if (angleAdd > 0.03)angleAdd = 0.03;
				Enemy::pos.x(cos(angle) * 300 + SCREEN_X / 2);
				Enemy::pos.y(sin(angle * 2) * 100 + SCREEN_Y / 3);
				Enemy::angle = GetRadian(270);
			}
			if (Enemy::frame >= 600 && Enemy::frame < 1200)
			{
				angle += angleAdd;
				angleAdd += 0.01;
				Enemy::pos.x(cos(angle) * 300 + SCREEN_X / 2);
				Enemy::pos.y(sin(angle * 2) * 100 + SCREEN_Y / 3);
				Enemy::angle = GetRadian(270);
			}
			if (Enemy::frame == 1200)Enemy::frame = 0;

			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_BOSS_SAMURAI:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 50)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 150)Enemy::angle = DX_PI;
			if (Enemy::frame == 200)Enemy::angle = DX_PI;
			if (Enemy::frame == 250)Enemy::angle = DX_PI;
			if (Enemy::frame == 300)Enemy::angle = 0;
			if (Enemy::frame == 350)Enemy::angle = 0;
			if (Enemy::frame == 400)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_BOSS_DRAGON:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 50)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 150)Enemy::angle = DX_PI;
			if (Enemy::frame == 200)Enemy::angle = DX_PI;
			if (Enemy::frame == 250)Enemy::angle = DX_PI;
			if (Enemy::frame == 300)Enemy::angle = 0;
			if (Enemy::frame == 350)Enemy::angle = 0;
			if (Enemy::frame == 400)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_BOSS_BIG_SNAKE:
		if (true)
		{
			int sp = 1;
			if (Enemy::frame == 0)Enemy::angle = 0;
			if (Enemy::frame == 50)Enemy::angle = 0;
			if (Enemy::frame == 100)Enemy::angle = DX_PI;
			if (Enemy::frame == 150)Enemy::angle = DX_PI;
			if (Enemy::frame == 200)Enemy::angle = DX_PI;
			if (Enemy::frame == 250)Enemy::angle = DX_PI;
			if (Enemy::frame == 300)Enemy::angle = 0;
			if (Enemy::frame == 350)Enemy::angle = 0;
			if (Enemy::frame == 400)Enemy::frame = 0;
			if (CheckDistance(Enemy::pos.x(), Enemy::pos.y(), player.pos.x(), player.pos.y()) < 200)
			{
				Enemy::angle = atan2((double)player.pos.y() - Enemy::pos.y(), player.pos.x() - Enemy::pos.x());
				sp = 3;
			}
			Enemy::pos.x(Enemy::pos.x() + cos(angle) * sp);
			Enemy::pos.y(Enemy::pos.y() + sin(angle) * sp + 1);
		}
		break;
	case ENEMY_TYPE_PARTS_BIG_LEG:
		if (true)
		{
			Enemy::angle += GetRadian(GetRand(10) - 5);
			Enemy::pos.x(enemy[0].pos.x() + cos(Enemy::angle) * 100);
			Enemy::pos.y(enemy[0].pos.y() + sin(Enemy::angle) * 100);
			int percent = (int)(1000.0 - frame / 10.0) > 0 ? (int)(1000.0 - frame / 10.0) : 0;
			//50分の1の確率で弾を発射します
			if (GetRand(percent) == 0)
			{
				Enemy::Shoot(BULLET_TYPE_GATLING);
			}
		}
		break;
	case ENEMY_TYPE_PARTS_CENTIPEDE_BODY:
		if (enemyId > 0)
		{
			int distance = CheckDistance(enemy[enemyId - 1].pos.x(), enemy[enemyId - 1].pos.y(), Enemy::pos.x(), Enemy::pos.y());
			if (distance > 30)
			{
				Enemy::angle = atan2((double)enemy[enemyId - 1].pos.y() - Enemy::pos.y(), (double)enemy[enemyId - 1].pos.x() - Enemy::pos.x());
				Enemy::pos.x(Enemy::pos.x() + cos(Enemy::angle) * 3);
				Enemy::pos.y(Enemy::pos.y() + sin(Enemy::angle) * 3);
			}
		}
		break;
	case ENEMY_TYPE_PARTS_MOTH_TAIL:
		if (true)
		{

		}
		break;
	case ENEMY_TYPE_PARTS_SAMURAI_HAND:
		break;
	case ENEMY_TYPE_PARTS_DRAGON_WING:
		break;
	case ENEMY_TYPE_PARTS_DRAGON_BODY:
		break;
	case ENEMY_TYPE_PARTS_BIG_SNAKE_CLAW:
		break;
	case ENEMY_TYPE_PARTS_BIG_SNAKE_HEAD:
		break;
	default:break;
	}
	//敵のフレームを進める
	Enemy::frame++;
}
//敵の種類によって出す弾を変える
void Enemy::Shoot(BulletType type)
{
	SetBullet(type, Enemy::pos.x() + cos(Enemy::angle) * enemyData[Enemy::type].radius, Enemy::pos.y() + sin(Enemy::angle) * enemyData[Enemy::type].radius, Enemy::angle, target_player);
}
bool Enemy::Delete(int enemyId)
{
	if (Enemy::life <= 0)
	{
		//ランダムな方向にエフェクトを飛ばします
		SetEffect(Position2D(enemy[enemyId].pos.x(), enemy[enemyId].pos.y()));
		//敵を消します
		enemy.erase(enemy.begin() + enemyId);
		return true;
	}
	else if (!(Enemy::pos.x() > 0 + enemyData[Enemy::type].radius &&
		Enemy::pos.x() < SCREEN_X - enemyData[Enemy::type].radius &&
		Enemy::pos.y() > 0 + enemyData[Enemy::type].radius &&
		Enemy::pos.y() < SCREEN_Y - enemyData[Enemy::type].radius))
	{
		if (Enemy::pos.y() > SCREEN_Y + enemyData[Enemy::type].radius &&
			Enemy::type < ENEMY_TYPE_BOSS_SPEED)
		{
			enemy.erase(enemy.begin() + enemyId);
			return true;
		}
		if (Enemy::pos.x() < 0 + enemyData[Enemy::type].radius)
		{
			Enemy::pos.x(0 + enemyData[Enemy::type].radius);
		}
		if (Enemy::pos.x() > SCREEN_X - enemyData[Enemy::type].radius)
		{
			Enemy::pos.x(SCREEN_X - enemyData[Enemy::type].radius);
		}
	}
	else
	{
		return false;
	}
}
void Enemy::CheckHit()
{
	if (CheckDistance(player.pos.x(), player.pos.y(), Enemy::pos.x(), Enemy::pos.y()) < 32 + enemyData[Enemy::type].radius)
	{
		player.life--;
	}
}
void Enemy::Draw()
{
	switch (Enemy::type)
	{
	case ENEMY_TYPE_PATROL:
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		break;
	case ENEMY_TYPE_SPIKE:
		for (int i = 0; i < 8; i++)
		{
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(i * 45 + Enemy::frame * 30), enemyData[Enemy::type].radius * 1.5);
		}
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		break;
	case ENEMY_TYPE_BOMB:
		for (int i = 0; i < 3; i++)
		{
			double tempAngle = GetRadian(i * 120) + Enemy::angle;
			int tempX = cos(tempAngle) * (enemyData[Enemy::type].radius);
			int tempY = sin(tempAngle) * (enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, tempAngle - GetRadian(90), enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, tempAngle + GetRadian(90), enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, Enemy::angle, enemyData[Enemy::type].radius / 2);
		}
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		break;
	case ENEMY_TYPE_SHOT:
		if (true)
		{
			int tempX = cos(Enemy::angle) * (enemyData[Enemy::type].radius / 1.4);
			int tempY = sin(Enemy::angle) * (enemyData[Enemy::type].radius / 1.4);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX / 2, Enemy::pos.y() - tempY / 2, Enemy::angle, enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX / 2, Enemy::pos.y() - tempY / 2, Enemy::angle + GetRadian(90), enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX / 2, Enemy::pos.y() - tempY / 2, Enemy::angle + GetRadian(180), enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX / 2, Enemy::pos.y() - tempY / 2, Enemy::angle + GetRadian(270), enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
			for (int i = 0; i < 6; i++)
			{
				double tempAngle = GetRadian(i * 60) + Enemy::angle;
				int tempX2 = cos(tempAngle) * (enemyData[Enemy::type].radius / 1.4);
				int tempY2 = sin(tempAngle) * (enemyData[Enemy::type].radius / 1.4);
				DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() + tempX + tempX2, Enemy::pos.y() + tempY + tempY2, Enemy::angle, enemyData[Enemy::type].radius / 2);
			}
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, Enemy::angle, enemyData[Enemy::type].radius / 2);
			for (int i = 0; i < 6; i++)
			{
				double tempAngle = GetRadian(i * 60) + Enemy::angle;
				int tempX2 = cos(tempAngle) * (enemyData[Enemy::type].radius / 1.4);
				int tempY2 = sin(tempAngle) * (enemyData[Enemy::type].radius / 1.4);
				DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x() + tempX + tempX2, Enemy::pos.y() + tempY + tempY2, Enemy::angle, enemyData[Enemy::type].radius / 2.5);
			}
			DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, Enemy::angle, enemyData[Enemy::type].radius / 2.5);
		}
		break;
	case ENEMY_TYPE_SNIPER:
		if (true)
		{
			int tempX = cos(Enemy::angle) * (enemyData[Enemy::type].radius * 2);
			int tempY = sin(Enemy::angle) * (enemyData[Enemy::type].radius * 2);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX / 1.3, Enemy::pos.y() - tempY / 1.3, Enemy::angle + GetRadian(180), enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX / 2, Enemy::pos.y() - tempY / 2, Enemy::angle - GetRadian(90), enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX / 2, Enemy::pos.y() - tempY / 2, Enemy::angle + GetRadian(90), enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() - tempX / 1.3, Enemy::pos.y() - tempY / 1.3, Enemy::angle, enemyData[Enemy::type].radius / 4);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() - tempX / 2, Enemy::pos.y() - tempY / 2, Enemy::angle, enemyData[Enemy::type].radius / 2.5);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() - tempX / 4, Enemy::pos.y() - tempY / 4, Enemy::angle, enemyData[Enemy::type].radius / 4);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 2);
			DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 3);
		}
		break;
	case ENEMY_TYPE_LASER:
		if (true)
		{
			int tempX = cos(Enemy::angle) * (enemyData[Enemy::type].radius);
			int tempY = sin(Enemy::angle) * (enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(90), enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(180), enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(270), enemyData[Enemy::type].radius * 1.6);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 2);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() + tempX / 4, Enemy::pos.y() + tempY / 4, Enemy::angle, enemyData[Enemy::type].radius / 2);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() + tempX / 2, Enemy::pos.y() + tempY / 2, Enemy::angle, enemyData[Enemy::type].radius / 2);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, Enemy::angle, enemyData[Enemy::type].radius / 1.5);
			DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, Enemy::angle, enemyData[Enemy::type].radius / 2);
		}
		break;
	case ENEMY_TYPE_VENOM:
		if (Enemy::frame % 4 == 0 || Enemy::frame % 4 == 1)
		{
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius, GetRadian(-20), enemyData[Enemy::type].radius * 2);
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius, GetRadian(200), enemyData[Enemy::type].radius * 2);
		}
		else
		{
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius, GetRadian(20), enemyData[Enemy::type].radius * 1.4);
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius, GetRadian(160), enemyData[Enemy::type].radius * 1.4);
		}
		for (int i = 0; i < 3; i++)
		{
			double tempAngle = GetRadian(i * 120 - 90);
			int tempX = cos(tempAngle) * (enemyData[Enemy::type].radius / 2);
			int tempY = sin(tempAngle) * (enemyData[Enemy::type].radius / 2);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, tempAngle, enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, Enemy::angle, enemyData[Enemy::type].radius / 2);
		}
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 2);
		break;
	case ENEMY_TYPE_TELEPORT:
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(-90), enemyData[Enemy::type].radius * 3);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(0), enemyData[Enemy::type].radius * 1.5);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(60), enemyData[Enemy::type].radius * 1.5);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(120), enemyData[Enemy::type].radius * 1.5);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(180), enemyData[Enemy::type].radius * 1.5);

		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		break;
	case ENEMY_TYPE_HOMING:
		if (Enemy::frame % 4 == 0 || Enemy::frame % 4 == 1)
		{
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-110), enemyData[Enemy::type].radius * 3);
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(110), enemyData[Enemy::type].radius * 3);
		}
		else
		{
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-70), enemyData[Enemy::type].radius * 2);
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(70), enemyData[Enemy::type].radius * 2);
		}
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-225), enemyData[Enemy::type].radius * 1.7);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-180), enemyData[Enemy::type].radius * 2);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-135), enemyData[Enemy::type].radius * 1.7);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius / 2, Enemy::angle, enemyData[Enemy::type].radius / 2);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y() + enemyData[Enemy::type].radius / 2, Enemy::angle, enemyData[Enemy::type].radius / 2);
		break;
	case ENEMY_TYPE_BOSS_SPEED:
		SetDrawBright(255, 63, 63);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(-90), enemyData[Enemy::type].radius * 2);
		for (int i = 0; i < 2; i++)
		{
			double tempAngle = GetRadian(i * 180 + 90) + Enemy::angle;
			int tempX = cos(tempAngle) * (enemyData[Enemy::type].radius * 1.4);
			int tempY = sin(tempAngle) * (enemyData[Enemy::type].radius * 1.4);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX, Enemy::pos.y() - tempY, tempAngle - GetRadian(90), enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x() - tempX, Enemy::pos.y() - tempY, tempAngle + GetRadian(90), enemyData[Enemy::type].radius);
			DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x() - tempX, Enemy::pos.y() - tempY, Enemy::angle, enemyData[Enemy::type].radius / 2.5);
		}
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		SetDrawBright(255, 255, 255);
		break;
	case ENEMY_TYPE_BOSS_BIG:
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		break;
	case ENEMY_TYPE_BOSS_CENTIPEDE:
		SetDrawBright(255, 127, 255);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle - GetRadian(45), enemyData[Enemy::type].radius * 2);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(45), enemyData[Enemy::type].radius * 2);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		SetDrawBright(255, 255, 255);
		break;
	case ENEMY_TYPE_BOSS_MOTH:
		SetDrawBright(127, 255, 127);
		if (Enemy::frame % 4 == 0 || Enemy::frame % 4 == 1)
		{
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-70), enemyData[Enemy::type].radius * 3);
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(70), enemyData[Enemy::type].radius * 3);
		}
		else
		{
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-110), enemyData[Enemy::type].radius * 2);
			DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(110), enemyData[Enemy::type].radius * 2);
		}
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		for (int i = 0; i < 6; i++)
		{
			double tempAngle = GetRadian(i * 60) + Enemy::angle;
			int tempX = cos(tempAngle) * (enemyData[Enemy::type].radius / 1.4);
			int tempY = sin(tempAngle) * (enemyData[Enemy::type].radius / 1.4);
			DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x() + tempX, Enemy::pos.y() + tempY, Enemy::angle, enemyData[Enemy::type].radius / 2.5);
		}
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 2.5);
		SetDrawBright(255, 255, 255);
		break;
	case ENEMY_TYPE_BOSS_SAMURAI:
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x() - enemyData[Enemy::type].radius / 2, Enemy::pos.y() + enemyData[Enemy::type].radius / 4, Enemy::angle, enemyData[Enemy::type].radius / 2.5);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x() + enemyData[Enemy::type].radius / 2, Enemy::pos.y() + enemyData[Enemy::type].radius / 4, Enemy::angle, enemyData[Enemy::type].radius / 2.5);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius / 4, GetRadian(-30), enemyData[Enemy::type].radius * 1.4);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius / 4, GetRadian(210), enemyData[Enemy::type].radius * 1.4);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius / 4, Enemy::angle, enemyData[Enemy::type].radius / 3);
		break;
	case ENEMY_TYPE_BOSS_DRAGON:
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius / 4, GetRadian(-50), enemyData[Enemy::type].radius * 1.6);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y() - enemyData[Enemy::type].radius / 4, GetRadian(230), enemyData[Enemy::type].radius * 1.6);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		break;
	case ENEMY_TYPE_BOSS_BIG_SNAKE:
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		break;
	case ENEMY_TYPE_PARTS_BIG_LEG:
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		break;
	case ENEMY_TYPE_PARTS_CENTIPEDE_BODY:
		SetDrawBright(255, 127, 255);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle - GetRadian(90), enemyData[Enemy::type].radius * 2);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(90), enemyData[Enemy::type].radius * 2);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		SetDrawBright(255, 255, 255);
		break;
	case ENEMY_TYPE_PARTS_MOTH_TAIL:
		SetDrawBright(127, 255, 127);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		SetDrawBright(255, 255, 255);
		break;
	case ENEMY_TYPE_PARTS_SAMURAI_HAND:
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius * 4);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		break;
	case ENEMY_TYPE_PARTS_DRAGON_WING:
		if (Enemy::angle > GetRadian(-90) && Enemy::angle < GetRadian(90))
		{
			if (Enemy::frame % 4 == 0 || Enemy::frame % 4 == 1)
			{
				DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-20), enemyData[Enemy::type].radius * 3);
			}
			else
			{
				DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(20), enemyData[Enemy::type].radius * 2);
			}
		}
		else
		{
			if (Enemy::frame % 4 == 0 || Enemy::frame % 4 == 1)
			{
				DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(20), enemyData[Enemy::type].radius * 3);
			}
			else
			{
				DrawEnemyParts(ENEMY_PARTS_WING, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle + GetRadian(-20), enemyData[Enemy::type].radius * 2);
			}
		}
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 4);
		break;
	case ENEMY_TYPE_PARTS_DRAGON_BODY:
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(-160), enemyData[Enemy::type].radius * 1.5);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(-130), enemyData[Enemy::type].radius * 1.7);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(-90), enemyData[Enemy::type].radius * 2);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(-60), enemyData[Enemy::type].radius * 1.7);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(-30), enemyData[Enemy::type].radius * 1.5);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		break;
	case ENEMY_TYPE_PARTS_BIG_SNAKE_CLAW:
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(45), enemyData[Enemy::type].radius * 1.7);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(90), enemyData[Enemy::type].radius * 2);
		DrawEnemyParts(ENEMY_PARTS_THORN, Enemy::pos.x(), Enemy::pos.y(), GetRadian(135), enemyData[Enemy::type].radius * 1.7);
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		break;
	case ENEMY_TYPE_PARTS_BIG_SNAKE_HEAD:
		DrawEnemyParts(ENEMY_PARTS_BODY, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius);
		DrawEnemyParts(ENEMY_PARTS_EYE, Enemy::pos.x(), Enemy::pos.y(), Enemy::angle, enemyData[Enemy::type].radius / 1.5);
		break;
	default:break;
	}
}
void LoadEnemyData()
{
	char tempString[256];
	for (int i = 0; i < ENEMY_TYPE_MAX; i++)
	{
		LoadCSV(tempString, "data/parameter/enemy.csv", i + 1, 0, ENEMY_TYPE_MAX, 3);
		enemyData[i].name = tempString;
		LoadCSV(tempString, "data/parameter/enemy.csv", i + 1, 1, ENEMY_TYPE_MAX, 3);
		enemyData[i].radius = atoi(tempString);
		LoadCSV(tempString, "data/parameter/enemy.csv", i + 1, 2, ENEMY_TYPE_MAX, 3);
		enemyData[i].lifeMax = atoi(tempString);
	}
}
void SetEnemy(EnemyType type, int x, int y)
{
	if (enemy.size() < 64)
	{
		enemy.push_back(Enemy(type, x, y));
	}
}
void DeleteAllEnemy()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		//ランダムな方向にエフェクトを飛ばします
		SetEffect(Position2D(enemy[i].pos.x(), enemy[i].pos.y()));
		//敵を消します
		enemy.erase(enemy.begin() + i);
	}
	enemy.clear();
}

void SetEnemyBoss(EnemyType type)
{
	DeleteAllEnemy();

	switch (type)
	{
	case ENEMY_TYPE_BOSS_SPEED:
		//enemy.push_back(Enemy(ENEMY_TYPE_BOSS_SPEED, SCREEN_X / 2, 0));
		SetEnemy(ENEMY_TYPE_BOSS_SPEED, SCREEN_X / 2, 0);
		break;
	case ENEMY_TYPE_BOSS_BIG:
		SetEnemy(ENEMY_TYPE_BOSS_BIG, SCREEN_X / 2, 0);
		for (int i = 0; i < 16; i++)
		{
			SetEnemy(ENEMY_TYPE_PARTS_BIG_LEG, SCREEN_X / 2, 0);
		}
		break;
	case ENEMY_TYPE_BOSS_CENTIPEDE:
		SetEnemy(ENEMY_TYPE_BOSS_CENTIPEDE, SCREEN_X / 2, 0);
		for (int i = 0; i < 30; i++)
		{
			SetEnemy(ENEMY_TYPE_PARTS_CENTIPEDE_BODY, SCREEN_X / 2, 0);
		}
		break;
	case ENEMY_TYPE_BOSS_MOTH:
		enemy.push_back(Enemy(ENEMY_TYPE_BOSS_MOTH, SCREEN_X / 2, 0));
		enemy.push_back(Enemy(ENEMY_TYPE_PARTS_MOTH_TAIL, SCREEN_X / 2, 0));
		break;
	case ENEMY_TYPE_BOSS_SAMURAI:
		break;
	case ENEMY_TYPE_BOSS_DRAGON:
		break;
	case ENEMY_TYPE_BOSS_BIG_SNAKE:
		break;
	default:return;
	}
}
