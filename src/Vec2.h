#pragma once
#include <SDL2pp/Point.hh>

typedef SDL2pp::Point Vec2;

inline double distance(const Vec2& a, const Vec2& b)
{
	Vec2 d = a - b;
	return std::sqrt(d.x * d.x + d.y * d.y);
}
