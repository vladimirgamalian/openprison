#include "Worker.h"
#include "Utils.h"
#include "World.h"

Worker::Worker(SDL2pp::Renderer& renderer, World* world) : renderer(renderer), world(world)
{
	for (int i = 0; i < 4; ++i)
	{
		std::string fileName = "data/people/worker/" + intTextureName(i) + ".png";
		textures[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	pos.x = 64;
	pos.y = 64;
}

void Worker::draw()
{
	int variant = 2;
	if (direction.y < 0)
		variant = 0;
	if (direction.y > 0)
		variant = 2;
	if (direction.x < 0)
		variant = 3;
	if (direction.x > 0)
		variant = 1;

	SDL2pp::Texture* texture = textures[variant].get();
	renderer.Copy(*texture, SDL2pp::NullOpt, pos);

	if (workerState == WorkerState::BuildWall)
	{

	}
}

void Worker::update()
{
	if (workerState == WorkerState::Donothing)
	{
		// Get a task from Worker Task Queue
		if (!world->popWorkerTask(workerTask))
			return;

		setTarget(workerTask.pos);
		workerState = WorkerState::Moving;
	}

	if (workerState == WorkerState::Moving)
		updateMoving();
	
	if (workerState == WorkerState::BuildWall)
		updateBuildWall();
}

void Worker::clearPath()
{
	path.clear();
	cursor = 0;
}

void Worker::addPath(const Vec2& pos)
{
	path.push_back(pos);
}

Vec2 Worker::getCellPos() const
{
	return Vec2(pos.x / 64, pos.y / 64);
}

void Worker::setTarget(const Vec2& pos)
{
	target = pos;
	resolvePath();
}

void Worker::resolvePath()
{
	clearPath();

	MP_VECTOR< void* > path;
	float totalCost = 0;
	int result = world->patherSolve(getCellPos(), target, path, &totalCost);

	if (!result)
		for (size_t i = 1; i < path.size(); ++i)
		{
			Vec2 p = world->graphStateToVec2(path[i]);
			//std::cout << graphStateToVec2(path[i]).x << ":" << graphStateToVec2(path[i]).y << std::endl;
			addPath(p * 64);
		}
}

void Worker::updateMoving()
{
	if (cursor >= path.size())
	{
		// Has got the target cell, run build animation
		workerState = WorkerState::BuildWall;
		buildWallPhase = 0;
		return;
	}

	Vec2 target = path[cursor];

	direction.reset();

	if (target.x > pos.x)
		direction.x = 1;
	else if (target.x != pos.x)
		direction.x = -1;

	if (target.y > pos.y)
		direction.y = 1;
	else if (target.y != pos.y)
		direction.y = -1;

	pos += direction;

	if ((target.x == pos.x) && (target.y == pos.y))
		cursor++;
}

void Worker::updateBuildWall()
{
	buildWallPhase++;
	if (buildWallPhase >= 120)
	{
		workerState = WorkerState::Donothing;
		world->setWall(workerTask.pos);
	}
}
