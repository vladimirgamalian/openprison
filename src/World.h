#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "Worker.h"
#include "micropather.h"

class World : private micropather::Graph
{
public:
	static const size_t COL_COUNT = 256;
	static const size_t ROW_COUNT = 256;

	World(SDL2pp::Renderer& renderer);
	void draw(float scale, float shiftX, float shiftY);
	void update();

	void setWall(const Vec2& pos);
	void removeWall(const Vec2& pos);

	void moveWorker(const Vec2& pos);

	int patherSolve(const Vec2& start, const Vec2& finish, MP_VECTOR< void* >& path, float* totalCost);

	SDL2pp::Point screenToWorld(int x, int y, float scale, float shiftX, float shiftY) const;

	Vec2 graphStateToVec2(void *node);

private:

	struct Tiles
	{
		enum
		{
			Space = 0,
			Border = 1,
			Wall = 2
		};
	};

	static bool isValidPos(const Vec2& pos)
	{
		return (pos.x > 0) && (pos.x < COL_COUNT - 1) && (pos.y > 0) && (pos.y < ROW_COUNT - 1);
	}
	static bool isValidPos(int x, int y)
	{
		return (x > 0) && (x < COL_COUNT - 1) && (y > 0) && (y < ROW_COUNT - 1);
	}


	void *vec2ToGraphState(const Vec2& point);
	virtual float LeastCostEstimate(void* stateStart, void* stateEnd);
	virtual void AdjacentCost(void* state, MP_VECTOR< micropather::StateCost > *adjacent);
	virtual void  PrintStateInfo(void* state) {};

	SDL2pp::Renderer& renderer;
	Worker worker;
	micropather::MicroPather microPather;
	SDL2pp::Texture dirt;
	SDL2pp::Texture border;
	SDL2pp::Texture tux;
	std::unique_ptr<SDL2pp::Texture> walls[16];


	uint32_t cells[ROW_COUNT][COL_COUNT];
	uint32_t cellsAttr[ROW_COUNT][COL_COUNT];
};
