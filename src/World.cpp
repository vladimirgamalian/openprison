#include "World.h"

World::World(SDL2pp::Renderer& renderer) : 
	renderer(renderer),
	dirt(renderer, "data/tileset/ground/dirt.png"),
	tux(renderer, "data/tux.png")
{

}

void World::draw(float scale)
{
	renderer.SetScale(scale, scale);

	for (size_t row = 0; row < ROW_COUNT; ++row)
	{
		for (size_t col = 0; col < COL_COUNT; ++col)
		{
			int w = 64;
			int h = 64;
			int x = col * w;
			int y = row * h;
			renderer.Copy(dirt, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
		}
	}

	renderer.SetScale(1.f, 1.f);
	renderer.Copy(tux, SDL2pp::NullOpt, SDL2pp::Point(0, 0));
}
