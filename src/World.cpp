#include "World.h"

World::World(SDL2pp::Renderer& renderer) : renderer(renderer), dirt(renderer, "data/tileset/ground/dirt.png")
{

}

void World::draw()
{
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
}
