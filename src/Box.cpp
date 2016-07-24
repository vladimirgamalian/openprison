#include "Box.h"

Box::Box(SDL2pp::Renderer& renderer) : 
	renderer(renderer), texture(renderer, "data/materials/box.png")
{

}

void Box::update()
{

}

void Box::draw(const Vec2& origin)
{
	renderer.Copy(texture, SDL2pp::NullOpt, origin + pos);
}

void Box::setPos(const Vec2& pos)
{
	this->pos = pos * 64;
}

void Box::setPosPx(const Vec2& pos)
{
	this->pos = pos;
}

Vec2 Box::getPos() const
{
	return pos / 64;
}
