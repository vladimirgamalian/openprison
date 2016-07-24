#pragma once
#include <vector>

class WorldScale
{
public:
	WorldScale();
	void update();
	void zoomIn();
	void zoomOut();
	float getSmooth() const;
	float get() const;
	
private:
	std::vector<float> scales;
	size_t scaleIndex;
	float smoothScale;
};
