#include "WorldScale.h"

const float WorldScale::ZOOM_STEP = 1.25f;
const float WorldScale::SCALE_MIN = 0.2f;
const float WorldScale::SCALE_MAX = 6.0f;

WorldScale::WorldScale()
{
	set(1.f);
}

void WorldScale::set(float scale)
{
	this->scale = scale;
	clampScale();
}

void WorldScale::zoomIn()
{
	scale *= ZOOM_STEP;
	clampScale();
}

void WorldScale::zoomOut()
{
	scale /= ZOOM_STEP;
	clampScale();
}

float WorldScale::get() const
{
	return scale;
}

void WorldScale::clampScale()
{
	if (scale < SCALE_MIN)
		scale = SCALE_MIN;
	if (scale > SCALE_MAX)
		scale = SCALE_MAX;
}
