#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "Worker.h"
#include "micropather.h"
#include "WorkerTaskQueue.h"
#include "Box.h"
#include "AreaSelection.h"
#include "Commuter.h"

class World : private micropather::Graph
{
public:
	static const size_t COL_COUNT = 96;
	static const size_t ROW_COUNT = 64;

	World(SDL2pp::Renderer& renderer);
	void draw(const Vec2& origin, float scale);
	void update();

	void setWall(const Vec2& pos);
	void removeWall(const Vec2& pos);
	void addWallBuildTask(const Vec2& pos);

	int patherSolve(const Vec2& start, const Vec2& finish, MP_VECTOR< void* >& path, float* totalCost);

	Vec2 graphStateToVec2(void *node);

	bool popWorkerTask(WorkerTask& workerTask);
	void pushWorkerTask(const WorkerTask& workerTask);

	void setAreaSelection(const SDL2pp::Rect& r);


private:

	struct Tiles
	{
		enum
		{
			Space = 0,
			Border,
			Wall,
			RoadLeft,
			RoadMiddle,
			RoadRight,
			RoadSpace,
			RoadSideWalk
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

	void generateBorders();
	void generateRoad(int col);

	void createWorker(const Vec2& pos);

	SDL2pp::Renderer& renderer;
	Box box;
	Commuter commuter;
	AreaSelection areaSelection;
	micropather::MicroPather microPather;
	SDL2pp::Texture border;
	SDL2pp::Texture tux;
	SDL2pp::Texture roadSideWalk;

	std::unique_ptr<SDL2pp::Texture> walls[16];
	std::unique_ptr<SDL2pp::Texture> dirts[16];

	std::unique_ptr<SDL2pp::Texture> roadLeft[2];
	std::unique_ptr<SDL2pp::Texture> roadMiddle[2];
	std::unique_ptr<SDL2pp::Texture> roadRight[2];
	std::unique_ptr<SDL2pp::Texture> roadSpace[4];
	
	
	WorkerTaskQueue workerTaskQueue;

	std::vector<WorldObject*> workers;

	uint32_t cells[ROW_COUNT][COL_COUNT];
	uint32_t cellsAttr[ROW_COUNT][COL_COUNT];
};
