#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "Vec2.h"
#include "WorkerTaskQueue.h"
#include "choreograph/Choreograph.h"

class World;

class Worker
{
public:
	Worker(SDL2pp::Renderer& renderer, World* world);
	void draw();
	void update();
	void clearPath();
	void addPath(const Vec2& pos);
	Vec2 getCellPos() const;
	void setTarget(const Vec2& pos);
	void resolvePath();
	void setPos(const Vec2& pos);

private:
	struct WorkerState
	{
		enum
		{
			Donothing,
			Moving,
			BuildWall
		};
	};

	void updateMoving();
	void updateBuildWall();

	SDL2pp::Renderer& renderer;
	World* world;
	choreograph::Sequence<float> buildWallAnimSeq;
	std::unique_ptr<SDL2pp::Texture> textures[4];
	SDL2pp::Texture hammer;
	Vec2 pos;
	std::vector<Vec2> path;
	size_t cursor = 0;
	Vec2 direction;
	Vec2 target;
	int workerState = WorkerState::Donothing;
	bool carrying = false;
	WorkerTask workerTask;
	int buildWallPhase;

};
