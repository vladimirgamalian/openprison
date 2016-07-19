#include "World.h"
#include "Utils.h"

World::World(SDL2pp::Renderer& renderer) : 
	renderer(renderer),
	dirt(renderer, "data/tileset/ground/dirt.png"),
	tux(renderer, "data/tux.png")
{
	for (int i = 0; i < 16; ++i)
	{
		std::string fileName = "data/tileset/wall/" + intTextureName(i) + ".png";
		walls[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	memset(cells, 0, ROW_COUNT * COL_COUNT);
	memset(cellsAttr, 0, ROW_COUNT * COL_COUNT);
	cells[0][0] = 1;
}

void World::draw(float scale, float shiftX, float shiftY)
{
	renderer.SetScale(scale, scale);

	for (size_t row = 0; row < ROW_COUNT; ++row)
	{
		for (size_t col = 0; col < COL_COUNT; ++col)
		{
			int w = 64;
			int h = 64;
			int x = static_cast<int>(shiftX) + col * w;
			int y = static_cast<int>(shiftY) + row * h;

			uint32_t cell = cells[row][col];
			uint32_t attr = cellsAttr[row][col];
			if (cell)
			{
				SDL2pp::Texture* texture = walls[attr % 16].get();
				renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
			}
			else
				renderer.Copy(dirt, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
		}
	}

	renderer.SetScale(1.f, 1.f);
	renderer.Copy(tux, SDL2pp::NullOpt, SDL2pp::Point(0, 0));
}

void World::setWall(int col, int row)
{
	if ((col < 0) || (col >= COL_COUNT))
		return;
	if ((row < 0) || (row >= ROW_COUNT))
		return;
	cells[row][col] = 1;
	cellsAttr[row][col] = 0;
}

SDL2pp::Point World::screenToWorld(int x, int y, float scale, float shiftX, float shiftY) const
{
	float resultX = static_cast<float>(x);
	float resultY = static_cast<float>(y);
	resultX /= scale;
	resultY /= scale;
	resultX += shiftX;
	resultY += shiftY;
	resultX /= 64;
	resultY /= 64;
	return SDL2pp::Point(static_cast<int>(resultX), static_cast<int>(resultY));
}
