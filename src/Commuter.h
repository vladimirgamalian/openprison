#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "WorldObject.h"
#include "Vec2.h"

class World;
class Worker;

class Commuter : public WorldObject
{
public:
	Commuter(SDL2pp::Renderer& renderer, World* world);
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

	Vec2 getRelSeatPos(int n) const;
	Vec2 getSeatPos(int n) const;
	void updateWorkersPos();

	SDL2pp::Renderer& renderer;
	World* world;
	SDL2pp::Texture texture;
	Vec2 pos;
	int state;
	int delay;
	Worker* workers[8];
};
