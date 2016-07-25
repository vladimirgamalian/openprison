#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "WorldObject.h"
#include "Vec2.h"

class Commuter : public WorldObject
{
public:
	Commuter(SDL2pp::Renderer& renderer);
	void reset();
	virtual void update() override;
	virtual void draw(const Vec2& origin) override;

private:
	struct State
	{
		enum
		{
			PreStart,
			MoveToStop,
			Stop,
			MoveToExit,
			Post
		};
	};
	SDL2pp::Renderer& renderer;
	SDL2pp::Texture texture;
	Vec2 pos;
	int state;
	int delay;
};
