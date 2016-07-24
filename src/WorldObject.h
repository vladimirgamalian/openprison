#pragma once
#include "Vec2.h"

class WorldObject
{
public:
	virtual void update() = 0;
	virtual void draw(const Vec2& origin) = 0;
};
