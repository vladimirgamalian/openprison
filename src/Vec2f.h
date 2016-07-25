#pragma once
#include "Vec2.h"

class Vec2f
{
public:
	float x;
	float y;
	Vec2f() : x(0.f), y(0.f) {}
	Vec2f(float x, float y) : x(x), y(y) {}
	Vec2f(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}
	Vec2f(const Vec2& v)
	{
		x = static_cast<float>(v.GetX());
		y = static_cast<float>(v.GetY());
	}

	Vec2 getVec2() const
	{
		//TODO: round
		return Vec2(static_cast<int>(x), static_cast<int>(y));
	}
	 
	//////////////////////////////////////////////////////////////////////////

	Vec2f operator + (const Vec2f& other) const
	{
		return Vec2f(x + other.x, y + other.y);
	}

	Vec2f operator - (const Vec2f& other) const
	{
		return Vec2f(x - other.x, y - other.y);
	}

	Vec2f operator * (const Vec2f& other) const
	{
		return Vec2f(x * other.x, y * other.y);
	}

	Vec2f operator / (const Vec2f& other) const
	{
		return Vec2f(x / other.x, y / other.y);
	}

	//////////////////////////////////////////////////////////////////////////

	Vec2f operator + (float value) const
	{
		return Vec2f(x + value, y + value);
	}

	Vec2f operator - (float value) const
	{
		return Vec2f(x - value, y - value);
	}

	Vec2f operator * (float value) const
	{
		return Vec2f(x * value, y * value);
	}

	Vec2f operator / (float value) const
	{
		return Vec2f(x / value, y / value);
	}

	//////////////////////////////////////////////////////////////////////////

	Vec2f& operator += (const Vec2f& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2f& operator -= (const Vec2f& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2f& operator *= (const Vec2f& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2f& operator /= (const Vec2f& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	Vec2f& operator += (float value)
	{
		x += value;
		y += value;
		return *this;
	}

	Vec2f& operator -= (float value)
	{
		x -= value;
		y -= value;
		return *this;
	}

	Vec2f& operator *= (float value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	Vec2f& operator /= (float value)
	{
		x /= value;
		y /= value;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
};
