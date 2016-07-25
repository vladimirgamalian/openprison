#pragma once
#include <vector>
#include "Vec2.h"
#include "Vec2f.h"

class WorldView
{
public:
	WorldView();
	void update();
	void zoomIn(const Vec2& centerPoint);
	void zoomOut(const Vec2& centerPoint);
	float getScale() const;
	Vec2f getShift() const;
	void setShift(const Vec2f& value);
	Vec2 screenToWorld(const Vec2& pos) const;
	void startDrag(const Vec2& screenPos);
	void drag(const Vec2& screenPos);

private:
	Vec2f getShiftByScale(const Vec2f& center, float scale0, float scale1) const;
	std::vector<float> scales;
	size_t scaleIndex;
	Vec2f shift;
	Vec2f startDragPos;
	Vec2f startDragShift;
};
