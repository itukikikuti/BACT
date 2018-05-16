#pragma once

#include <vector>
#include "position.h"

class Effect{
public:
	int type;
	Position2D pos;
	Position3D velocity;
	int radius;
	Effect();
	Effect(int type, Position2D pos, Position3D velocity, int radius);
	~Effect();
	void Set(int type, Position2D pos, Position3D velocity, int radius);
	void Move();
	bool Delete(int effectId);
	void Draw();
};

extern std::vector<Effect> effect;

extern void SetEffect(Position2D pos);