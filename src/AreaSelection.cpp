#include "AreaSelection.h"

AreaSelection::AreaSelection(SDL2pp::Renderer& renderer) :
	renderer(renderer)
{

}

void AreaSelection::update()
{

}

void AreaSelection::draw()
{
	renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
	renderer.SetDrawColor(50, 250, 50, 100);
	renderer.FillRect(area);
}

void AreaSelection::set(const SDL2pp::Rect& r)
{
	area = SDL2pp::Rect({ r.GetX() * 64,  r.GetY() * 64,  r.GetW() * 64,  r.GetH() * 64});
}
