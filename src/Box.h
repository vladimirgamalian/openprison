#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "WorldObject.h"
#include "Vec2.h"

class Box : private WorldObject
{
public:
	Box(SDL2pp::Renderer& renderer);

	virtual void update() override;
	virtual void draw(const Vec2& origin) override;

	void setPos(const Vec2& pos);
	void setPosPx(const Vec2& pos);
	Vec2 getPos() const;

private:
	SDL2pp::Renderer& renderer;
	SDL2pp::Texture texture;
	Vec2 pos;
};
