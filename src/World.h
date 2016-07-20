#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "Worker.h"

class World
{
public:
	static const size_t COL_COUNT = 256;
	static const size_t ROW_COUNT = 256;

	World(SDL2pp::Renderer& renderer);
	void draw(float scale, float shiftX, float shiftY);
	void update();

	void setWall(int col, int row);
	void removeWall(int col, int row);

	SDL2pp::Point screenToWorld(int x, int y, float scale, float shiftX, float shiftY) const;

private:
	uint32_t getCell(int col, int row) const;
	uint32_t getCellUp(int col, int row) const;
	uint32_t getCellRight(int col, int row) const;
	uint32_t getCellDown(int col, int row) const;
	uint32_t getCellLeft(int col, int row) const;

	SDL2pp::Renderer& renderer;
	Worker worker;
	SDL2pp::Texture dirt;
	SDL2pp::Texture tux;
	std::unique_ptr<SDL2pp::Texture> walls[16];


	uint32_t cells[ROW_COUNT][COL_COUNT];
	uint32_t cellsAttr[ROW_COUNT][COL_COUNT];
};