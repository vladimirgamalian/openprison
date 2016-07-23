#pragma once
#include "WorldObject.h"
#include <SDL2pp/SDL2pp.hh>

class AreaSelection : public WorldObject
{
public:
	AreaSelection(SDL2pp::Renderer& renderer);
	virtual void update() override;
	virtual void draw() override;
	void set(const SDL2pp::Rect& r);

private:
	SDL2pp::Renderer& renderer;
	SDL2pp::Rect area;
};
