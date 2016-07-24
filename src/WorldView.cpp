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

	smoothScale = SCALE_BASE;
	shiftX = 0;
	shiftY = 0;
}

void WorldView::update()
{
	const float SMOOTH_STEP = 0.1f;
	float targetScale = getScale();

	float delta = targetScale - smoothScale;
	if (fabs(delta) < 0.01f)
		smoothScale = targetScale;
	else
		smoothScale += (delta * 0.2f);
}

void WorldView::zoomIn(const Vec2& centerPoint)
{
	if ((scaleIndex + 1) >= scales.size())
		return;

	Vec2 v = screenToWorld(centerPoint);
	scaleIndex++;
	Vec2 d = screenToWorld(centerPoint) - v;
	shiftX += d.GetX();
	shiftY += d.GetY();
}

void WorldView::zoomOut(const Vec2& centerPoint)
{
	if (!scaleIndex)
		return;

	Vec2 v = screenToWorld(centerPoint);
	scaleIndex--;
	Vec2 d = screenToWorld(centerPoint) - v;
	shiftX += d.GetX();
	shiftY += d.GetY();
}

float WorldView::getScale() const
{
	return scales[scaleIndex];
}

Vec2 WorldView::getShift() const
{
	//TODO: round
	return Vec2(static_cast<int>(shiftX), static_cast<int>(shiftY));
}

Vec2f WorldView::getShiftF() const
{
	return Vec2f(shiftX, shiftY);
}

float WorldView::getShiftX() const
{
	return shiftX;
}

float WorldView::getShiftY() const
{
	return shiftY;
}

Vec2 WorldView::screenToWorld(const Vec2& pos) const
{
	float resultX = static_cast<float>(pos.GetX());
	float resultY = static_cast<float>(pos.GetY());
	resultX /= getScale();
	resultY /= getScale();
	resultX -= shiftX;
	resultY -= shiftY;
	return SDL2pp::Point(static_cast<int>(resultX), static_cast<int>(resultY));
}

void WorldView::setShift(const Vec2f& value)
{
	this->shiftX = value.x;
	this->shiftY = value.y;
}
