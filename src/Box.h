#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "Vec2.h"

class Box
{
public:
	Box(SDL2pp::Renderer& renderer);
	void draw();
	void setPos(const Vec2& pos);
	void setPosPx(const Vec2& pos);
	Vec2 getPos() const;

private:
	SDL2pp::Renderer& renderer;
	SDL2pp::Texture texture;
	Vec2 pos;
};
