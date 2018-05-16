#include "DxLib.h"
#include <math.h>
#include "main.h"
#include "player.h"
#include "graphic.h"
#include "effect.h"

std::vector<Effect> effect;

Effect::Effect()
{
	Effect::type = 0;
	Effect::pos = Position2D(0, 0);
	Effect::velocity = Position3D(0, 0, 0);
	Effect::radius = 0;
}
Effect::Effect(int type, Position2D pos, Position3D velocity, int radius)
{
	Effect::type = type;
	Effect::pos = pos;
	Effect::velocity = velocity;
	Effect::radius = radius;
}
Effect::~Effect()
{

}
void Effect::Set(int type, Position2D pos, Position3D velocity, int radius)
{
	Effect::type = type;
	Effect::pos = pos;
	Effect::velocity = velocity;
	Effect::radius = radius;
}
void Effect::Move()
{
	float angle = atan2(player.pos.y() - Effect::pos.y(), player.pos.x() - Effect::pos.x());
	Effect::velocity.x(Effect::velocity.x() * 0.95 + cos(angle));
	Effect::velocity.y(Effect::velocity.y() * 0.95 + sin(angle));
	Effect::pos.x(Effect::pos.x() + Effect::velocity.x());
	Effect::pos.y(Effect::pos.y() + Effect::velocity.y());
}
bool Effect::Delete(int effectId)
{
	if (CheckDistance(player.pos.x(), player.pos.y(), Effect::pos.x(), Effect::pos.y()) < 32)
	{
		if (Effect::type == 0 &&
			player.bulletLevel[player.holdWeapon] < 4000)
		{
			player.bulletLevel[player.holdWeapon]++;
		}
		if (Effect::type == 1)
		{
		}
		if (Effect::type == 2 &&
			player.bulletAmmo[player.holdWeapon] < bulletData[player.holdWeapon].ammoMax)
		{
			player.bulletAmmo[player.holdWeapon]++;
		}
		effect.erase(effect.begin() + effectId);
		return true;
	}
	return false;
}
void Effect::Draw()
{
	static Graphic red("data/img/effect/red.png");
	static Graphic green("data/img/effect/green.png");
	static Graphic blue("data/img/effect/blue.png");

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	if (Effect::type == 0)DrawRotaGraph(Effect::pos.x(), Effect::pos.y(), Effect::radius / (red.width() / 2.0), 0, red.handle(), true);
	if (Effect::type == 1)DrawRotaGraph(Effect::pos.x(), Effect::pos.y(), Effect::radius / (green.width() / 2.0), 0, green.handle(), true);
	if (Effect::type == 2)DrawRotaGraph(Effect::pos.x(), Effect::pos.y(), Effect::radius / (blue.width() / 2.0), 0, blue.handle(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
void SetEffect(Position2D pos)
{
	for (int i = 0; i < 20; i++)
	{
		if (effect.size() < 256)
		{
			float angle = GetRadian(GetRand(360));
			float speed = 20 + (GetRand(4) - 2);
			int type = 0;
			if (GetRand(9) == 0)type = 1;
			if (GetRand(bulletData[player.holdWeapon].ammoMax * bulletData[player.holdWeapon].setNum) == 0)
			{
				type = 2;
			}
			effect.push_back(Effect(type, pos, Position3D(cos(angle) * speed, sin(angle) * speed, 0), 16));
		}
	}
}