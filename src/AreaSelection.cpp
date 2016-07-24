#include "AreaSelection.h"

AreaSelection::AreaSelection(SDL2pp::Renderer& renderer) :
	renderer(renderer),
	animSeq(100)
{
	animSeq.then<choreograph::RampTo>(200, 1.0, choreograph::EaseInQuad())
		.then<choreograph::RampTo>(100, 1.0, choreograph::EaseOutQuad());
	animLoop.setDuration(animSeq.getDuration());
}

void AreaSelection::update()
{
	animLoop.step();
}

void AreaSelection::draw(const Vec2& origin)
{
	Uint8 a = static_cast<Uint8>(animSeq.getValue(animLoop.get()));

	renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
	renderer.SetDrawColor(50, 250, 50, a);
	renderer.FillRect(area + origin);
}

void AreaSelection::set(const SDL2pp::Rect& r)
{
	area = SDL2pp::Rect(r.GetX() * 64,  r.GetY() * 64,  r.GetW() * 64,  r.GetH() * 64);
}
