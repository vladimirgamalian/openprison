#pragma once
#include "WorldObject.h"
#include <SDL2pp/SDL2pp.hh>
#include "choreograph/Choreograph.h"
#include "AnimLoop.h"

class AreaSelection : public WorldObject
{
public:
	AreaSelection(SDL2pp::Renderer& renderer);
	virtual void update() override;
	virtual void draw(const Vec2& origin) override;
	void set(const SDL2pp::Rect& r);

private:
	SDL2pp::Renderer& renderer;
	SDL2pp::Rect area;
	choreograph::Sequence<float> animSeq;
	AnimLoop animLoop;
};
