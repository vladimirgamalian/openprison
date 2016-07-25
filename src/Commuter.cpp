#include "Commuter.h"
#include "World.h"

Commuter::Commuter(SDL2pp::Renderer& renderer, World* world) :
	renderer(renderer), world(world), texture(renderer, "data/cars/commuter.png")
{
	reset();
}

void Commuter::reset()
{
	pos = Vec2(5 * 64 + 16, 0);
	state = State::PreStart;
}

void Commuter::update()
{
	switch (state)
	{
	case State::PreStart:
		//TODO: magic const
		for (int n = 0; n < 8; ++n)
			workers[n] = world->createWorker(getSeatPos(n));

		state = State::MoveToStop;
		break;
	case State::MoveToStop:
		pos.SetY(pos.GetY() + 1);
		updateWorkersPos();
		if (pos.GetY() > 12 * 64)
		{
			state = State::Stop;
			delay = 180;
		}
		break;
	case State::Stop:
		if (delay)
			delay--;
		else
			state = State::MoveToExit;
		break;
	case State::MoveToExit:
		pos.SetY(pos.GetY() + 1);
		if (pos.GetY() > 48 * 64)
		{
			state = State::Post;
		}
		break;
	case State::Post:
		break;
	}
}

void Commuter::draw(const Vec2& origin)
{
	renderer.Copy(texture, SDL2pp::NullOpt, origin + pos);
}

Vec2 Commuter::getRelSeatPos(int n) const
{
	int col = n % 2;
	int row = n / 2;
	return {col * 64, row * 64 + 32};
}

Vec2 Commuter::getSeatPos(int n) const
{
	return pos + getRelSeatPos(n);
}

void Commuter::updateWorkersPos()
{
	//TODO: magic const
	for (int n = 0; n < 8; ++n)
		workers[n]->setPos(getSeatPos(n));
}
