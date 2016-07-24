#pragma once

class WorldScale
{
public:
	WorldScale();

	void set(float scale);
	void zoomIn();
	void zoomOut();

	float get() const;
	
private:
	static const float ZOOM_STEP;
	static const float SCALE_MIN;
	static const float SCALE_MAX;
	void clampScale();
	float scale = 1.0f;
};
