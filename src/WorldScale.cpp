#include "WorldScale.h"
#include <deque>
#include <iterator>

WorldScale::WorldScale()
{
	const float ZOOM_STEP = 1.25f;
	const float SCALE_BASE = 0.5f;
	const float SCALE_MIN = 0.2f;
	const float SCALE_MAX = 6.0f;

	std::deque<float> d;

	float scale = SCALE_BASE;
	for (;;)
	{
		scale /= ZOOM_STEP;
		if (scale < SCALE_MIN)
			break;
		d.push_front(scale);
	}

	scaleIndex = d.size();

	scale = SCALE_BASE;
	while (scale < SCALE_MAX)
	{
		d.push_back(scale);
		scale *= ZOOM_STEP;
	}

	std::copy(d.cbegin(), d.cend(), std::back_inserter(scales));

	smoothScale = SCALE_BASE;
}

void WorldScale::update()
{
	const float SMOOTH_STEP = 0.1f;
	float targetScale = scales[scaleIndex];

	float delta = targetScale - smoothScale;
	if (fabs(delta) < 0.01f)
		smoothScale = targetScale;
	else
		smoothScale += (delta * 0.2f);
}

void WorldScale::zoomIn()
{
	if ((scaleIndex + 1) < scales.size())
		scaleIndex++;
}

void WorldScale::zoomOut()
{
	if (scaleIndex > 0)
		scaleIndex--;
}

float WorldScale::get() const
{
	return smoothScale;
}
