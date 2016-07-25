#include "Commuter.h"

Commuter::Commuter(SDL2pp::Renderer& renderer) :
	renderer(renderer), texture(renderer, "data/cars/commuter.png")
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
		state = State::MoveToStop;
		break;
	case State::MoveToStop:
		pos.SetY(pos.GetY() + 1);
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
