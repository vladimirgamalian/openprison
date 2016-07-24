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
	Vec2 getShift() const;
	Vec2f getShiftF() const;
	float getShiftX() const;
	float getShiftY() const;
	Vec2 screenToWorld(const Vec2& pos) const;
	void setShift(const Vec2f& value);
	
private:
	std::vector<float> scales;
	size_t scaleIndex;
	float smoothScale;
	//TODO: Vec2f
	float shiftX;
	float shiftY;
};
