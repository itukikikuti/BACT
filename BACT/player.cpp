#include "DxLib.h"
#include "main.h"
#include "player.h"

Player player;

Player::Player()
{
	Player::type = 0;
	Player::pos = Position2D(0, 0);
	Player::speed = 0;
	Player::life = 0;
	holdWeapon = BULLET_TYPE_SHOT;
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		bulletFlag[i] = true;
		bulletWait[i] = 0;
		bulletLevel[i] = 0;
		bulletAmmo[i] = bulletData[i].ammoMax;
	}
}
Player::Player(int x, int y)
{
	Player::type = 0;
	Player::pos = Position2D(x, y);
	Player::speed = 0;
	Player::life = 0;
	holdWeapon = BULLET_TYPE_SHOT;
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		bulletFlag[i] = true;
		bulletWait[i] = 0;
		bulletLevel[i] = 0;
		bulletAmmo[i] = bulletData[i].ammoMax;
	}
}
Player::~Player()
{

}
void Player::Set(int x, int y)
{
	Player::pos = Position2D(x, y);
}
void Player::Move()
{
	int vx = 0, vy = 0;

	if (key.GetKey(KEY_INPUT_UP))vy = -Player::speed;
	if (key.GetKey(KEY_INPUT_DOWN))vy = Player::speed;
	if (key.GetKey(KEY_INPUT_LEFT))vx = -Player::speed;
	if (key.GetKey(KEY_INPUT_RIGHT))vx = Player::speed;

	Player::pos += Position2D(vx, vy);

	if (Player::pos.x() < 0){ Player::pos.x(0); }
	if (Player::pos.x() > SCREEN_X){ Player::pos.x(SCREEN_X); }
	if (Player::pos.y() < 0){ Player::pos.y(0); }
	if (Player::pos.y() > SCREEN_Y){ Player::pos.y(SCREEN_Y); }
}
void Player::Shoot()
{
	if (key.GetKey(KEY_INPUT_Z) &&
		bulletWait[holdWeapon] == 0 &&
		bulletAmmo[holdWeapon] > 0)
	{
		SetBullet(holdWeapon, Player::pos.x(), Player::pos.y(), GetRadian(-90));
		int l = player.bulletLevel[player.holdWeapon] / 1000 + 1;	//ƒŒƒxƒ‹
		bulletWait[holdWeapon] = bulletData[holdWeapon].resetWait / (double)l;
		bulletAmmo[holdWeapon]--;
	}

	if (bulletWait[holdWeapon] > 0)bulletWait[holdWeapon]--;
	else bulletWait[holdWeapon] = 0;
}
void Player::Eat()
{
	static Graphic berserker("data/img/char/berserkerBack.png");
	static Graphic chaser("data/img/char/chaserBack.png");
	static Graphic assassin("data/img/char/assassinBack.png");
	
	if (Player::type == 0)DrawRotaGraph(Player::pos.x(), Player::pos.y(), 1, 0, berserker.handle(), true);
	if (Player::type == 1)DrawRotaGraph(Player::pos.x(), Player::pos.y(), 1, 0, chaser.handle(), true);
	if (Player::type == 2)DrawRotaGraph(Player::pos.x(), Player::pos.y(), 1, 0, assassin.handle(), true);
}
void Player::Draw()
{
	static Graphic berserker("data/img/char/berserkerBack.png");
	static Graphic chaser("data/img/char/chaserBack.png");
	static Graphic assassin("data/img/char/assassinBack.png");
	if (Player::type == 0)DrawRotaGraph(Player::pos.x(), Player::pos.y(), 1, 0, berserker.handle(), true);
	if (Player::type == 1)DrawRotaGraph(Player::pos.x(), Player::pos.y(), 1, 0, chaser.handle(), true);
	if (Player::type == 2)DrawRotaGraph(Player::pos.x(), Player::pos.y(), 1, 0, assassin.handle(), true);
}