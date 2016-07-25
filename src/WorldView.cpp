#include "WorldView.h"
#include <deque>
#include <iterator>

WorldView::WorldView()
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
}

void WorldView::update()
{

}

void WorldView::zoomIn(const Vec2& centerPoint)
{
	if ((scaleIndex + 1) >= scales.size())
		return;

	float prevScale = getScale();
	scaleIndex++;
	shift += getShiftByScale(centerPoint, prevScale, getScale());
}

void WorldView::zoomOut(const Vec2& centerPoint)
{
	if (!scaleIndex)
		return;

	float prevScale = getScale();
	scaleIndex--;
	shift += getShiftByScale(centerPoint, prevScale, getScale());
}

float WorldView::getScale() const
{
	return scales[scaleIndex];
}

Vec2f WorldView::getShift() const
{
	return shift;
}

Vec2 WorldView::screenToWorld(const Vec2& pos) const
{
	Vec2f result = Vec2f(pos);
	result /= getScale();
	result -= shift;
	return result.getVec2();
}

void WorldView::startDrag(const Vec2& screenPos)
{
	startDragPos = Vec2f(screenPos) / getScale();
	startDragShift = getShift();
}

void WorldView::drag(const Vec2& screenPos)
{
	Vec2f s = (Vec2f(screenPos) / getScale()) - startDragPos;
	setShift(startDragShift + s);
}

void WorldView::setShift(const Vec2f& value)
{
	shift = value;
}

Vec2f WorldView::getShiftByScale(const Vec2f& center, float scale0, float scale1) const
{
	return center * ((1.f / scale1) - (1.f / scale0));
}
