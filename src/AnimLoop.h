#pragma once
#include "choreograph/Choreograph.h"

class AnimLoop
{
public:
	void setDuration(choreograph::Time duration)
	{
		this->duration = duration;
		reset();
	}

	void reset()
	{
		cur = 0;
	}

	void step(float v = 1.f / 60.f)
	{
		cur += v;
		if (cur > duration)
			cur -= duration;
	}

	float get() const
	{
		return cur;
	}

private:
	choreograph::Time duration = 0;
	choreograph::Time cur = 0;
};
