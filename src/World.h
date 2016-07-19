#pragma once
#include <SDL2pp/SDL2pp.hh>

class World
{
public:
	static const size_t COL_COUNT = 256;
	static const size_t ROW_COUNT = 256;

	World(SDL2pp::Renderer& renderer);
	void draw();

private:
	SDL2pp::Renderer& renderer;
	SDL2pp::Texture dirt;
};
