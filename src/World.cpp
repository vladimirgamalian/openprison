#include "World.h"
#include "Utils.h"

World::World(SDL2pp::Renderer& renderer) : 
	renderer(renderer),
	box(renderer),
	commuter(renderer),
	areaSelection(renderer),
	microPather(this),
	border(renderer, "data/tileset/border.png"),
	tux(renderer, "data/tux.png"),
	roadSideWalk(renderer, "data/tileset/road/sidewalk.png")
{
	for (int i = 0; i < 16; ++i)
	{
		std::string fileName = "data/tileset/wall/" + intTextureName(i) + ".png";
		walls[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = "data/tileset/ground/dirt/" + intTextureName(i) + ".png";
		dirts[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	for (int i = 0; i < 2; ++i)
	{
		std::string fileName = "data/tileset/road/left/" + intTextureName(i) + ".png";
		roadLeft[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));

		fileName = "data/tileset/road/middle/" + intTextureName(i) + ".png";
		roadMiddle[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));

		fileName = "data/tileset/road/right/" + intTextureName(i) + ".png";
		roadRight[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}

	for (int i = 0; i < 4; ++i)
	{
		std::string fileName = "data/tileset/road/space/" + intTextureName(i) + ".png";
		roadSpace[i] = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(renderer, fileName));
	}


	memset(cells, static_cast<int>(Tiles::Space), ROW_COUNT * COL_COUNT * sizeof(uint32_t));
	memset(cellsAttr, 0, ROW_COUNT * COL_COUNT);

	for (size_t row = 0; row < ROW_COUNT; row++)
		for (size_t col = 0; col < COL_COUNT; col++)
			cellsAttr[row][col] = rand();

	generateBorders();
	generateRoad(4);


	createWorker({ 3, 2 });
	createWorker({ 3, 3 });

	box.setPos({ 15, 2 });

	workerTaskQueue.push(WorkerTask(WorkerTask::TaskType::MoveBox, {7, 4}, &box));
}

void World::addWallBuildTask(const Vec2& pos)
{
	workerTaskQueue.push(WorkerTask(WorkerTask::TaskType::BuildWall, pos));
}

void World::draw(const Vec2& origin, float scale)
{
	renderer.SetScale(scale, scale);

	for (size_t row = 0; row < ROW_COUNT; ++row)
	{
		for (size_t col = 0; col < COL_COUNT; ++col)
		{
			int w = 64;
			int h = 64;
			int x = origin.GetX() + col * w;
			int y = origin.GetY() + row * h;

			uint32_t cell = cells[row][col];
			uint32_t attr = cellsAttr[row][col];

			switch (cell)
			{
			case Tiles::Wall:
				{
					SDL2pp::Texture* texture = walls[attr % 16].get();
					renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
				}
				break;
			case Tiles::Border:
				renderer.Copy(border, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
				break;
			case Tiles::Space:
				{
					SDL2pp::Texture* texture = dirts[attr % 10].get();
					renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
				}
				break;
			case Tiles::RoadLeft:
			{
				SDL2pp::Texture* texture = roadLeft[attr % 2].get();
				renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
			}
			break;
			case Tiles::RoadMiddle:
			{
				SDL2pp::Texture* texture = roadMiddle[attr % 2].get();
				renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
			}
			break;
			case Tiles::RoadRight:
			{
				SDL2pp::Texture* texture = roadRight[attr % 2].get();
				renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
			}
			break;
			case Tiles::RoadSpace:
			{
				SDL2pp::Texture* texture = roadSpace[attr % 2].get();
				renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
			}
			break;
			case Tiles::RoadSideWalk:
				renderer.Copy(roadSideWalk, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
				break;

			}

		}
	}

	areaSelection.draw(origin);

	commuter.draw(origin);

	box.draw(origin);

	for (auto i : workers)
		i->draw(origin);

	renderer.SetScale(1.f, 1.f);
	renderer.Copy(tux, SDL2pp::NullOpt, SDL2pp::Point(0, 400));
}

void World::update()
{
	for (auto i : workers)
		i->update();

	areaSelection.update();
	commuter.update();
}

void World::setWall(const Vec2& pos)
{
	if (!isValidPos(pos))
		return;

	cells[pos.y][pos.x] = static_cast<int>(Tiles::Wall);

	uint32_t attr = 0;
	if (cells[pos.y - 1][pos.x] == Tiles::Wall)		// up
	{
		attr |= 1;
		cellsAttr[pos.y - 1][pos.x] |= 4;
	}
	if (cells[pos.y][pos.x + 1] == Tiles::Wall)		// right
	{
		attr |= 2;
		cellsAttr[pos.y][pos.x + 1] |= 8;
	}
	if (cells[pos.y + 1][pos.x] == Tiles::Wall)		// down
	{
		attr |= 4;
		cellsAttr[pos.y + 1][pos.x] |= 1;
	}
	if (cells[pos.y][pos.x - 1] == Tiles::Wall)		// left
	{
		attr |= 8;
		cellsAttr[pos.y][pos.x - 1] |= 2;
	}

	cellsAttr[pos.y][pos.x] = attr;

	microPather.Reset();

	//TODO: oprimize
	for (auto i : workers)
		reinterpret_cast<Worker*>(i)->resolvePath();
}

void World::removeWall(const Vec2& pos)
{
	if (!isValidPos(pos))
		return;

	cells[pos.y][pos.x] = static_cast<int>(Tiles::Space);

	if (cells[pos.y - 1][pos.x] == Tiles::Wall)		// up
		cellsAttr[pos.y - 1][pos.x] &= ~4;
	if (cells[pos.y][pos.x + 1] == Tiles::Wall)		// right
		cellsAttr[pos.y][pos.x + 1] &= ~8;
	if (cells[pos.y + 1][pos.x] == Tiles::Wall)		// down
		cellsAttr[pos.y + 1][pos.x] &= ~1;
	if (cells[pos.y][pos.x - 1] == Tiles::Wall)		// left
		cellsAttr[pos.y][pos.x - 1] &= ~2;

	microPather.Reset();
	for (auto i : workers)
		reinterpret_cast<Worker*>(i)->resolvePath();
}

Vec2 World::graphStateToVec2(void *node)
{
	uintptr_t index = reinterpret_cast<uintptr_t>(node);
	int y = index / COL_COUNT;
	int x = index - y * COL_COUNT;
	return Vec2(x, y);
}

void *World::vec2ToGraphState(const Vec2& point)
{
	return reinterpret_cast<void*>(static_cast<uintptr_t>(point.y * COL_COUNT + point.x));
}

float World::LeastCostEstimate(void* stateStart, void* stateEnd)
{
	Vec2 start = graphStateToVec2(stateStart);
	Vec2 end = graphStateToVec2(stateEnd);
	return static_cast<float>(distance(start, end));
}

void World::AdjacentCost(void* state, MP_VECTOR< micropather::StateCost > *adjacent)
{
	Vec2 pos = graphStateToVec2(state);

	bool up = false;
	if (cells[pos.y - 1][pos.x] == Tiles::Space)		// up
	{
		up = true;
		micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x, pos.y - 1)), 1.f };
		adjacent->push_back(nodeCost);
	}
	bool right = false;
	if (cells[pos.y][pos.x + 1] == Tiles::Space)		// right
	{
		right = true;
		micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x + 1, pos.y)), 1.f };
		adjacent->push_back(nodeCost);
	}
	bool down = false;
	if (cells[pos.y + 1][pos.x] == Tiles::Space)		// down
	{
		down = true;
		micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x, pos.y + 1)), 1.f };
		adjacent->push_back(nodeCost);
	}
	bool left = false;
	if (cells[pos.y][pos.x - 1] == Tiles::Space)		// left
	{
		left = true;
		micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x - 1, pos.y)), 1.f };
		adjacent->push_back(nodeCost);
	}

	if (up && right)
	{
		if (cells[pos.y - 1][pos.x + 1] == Tiles::Space)		// up-right
		{
			micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x + 1, pos.y - 1)), 1.41f };
			adjacent->push_back(nodeCost);
		}
	}

	if (right && down)
	{
		if (cells[pos.y + 1][pos.x + 1] == Tiles::Space)		// right-down
		{
			micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x + 1, pos.y + 1)), 1.41f };
			adjacent->push_back(nodeCost);
		}
	}

	if (down && left)
	{
		if (cells[pos.y + 1][pos.x - 1] == Tiles::Space)		// down-left
		{
			micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x - 1, pos.y + 1)), 1.41f };
			adjacent->push_back(nodeCost);
		}
	}

	if (left && up)
	{
		if (cells[pos.y - 1][pos.x - 1] == Tiles::Space)		// left-up
		{
			micropather::StateCost nodeCost = { vec2ToGraphState(Vec2(pos.x - 1, pos.y - 1)), 1.41f };
			adjacent->push_back(nodeCost);
		}
	}
}

int World::patherSolve(const Vec2& start, const Vec2& finish, MP_VECTOR< void* >& path, float* totalCost)
{
	return microPather.Solve(vec2ToGraphState(start), vec2ToGraphState(finish), &path, totalCost);
}

bool World::popWorkerTask(WorkerTask& workerTask)
{
	return workerTaskQueue.pop(workerTask);
}

void World::pushWorkerTask(const WorkerTask& workerTask)
{
	workerTaskQueue.push(workerTask);
}

void World::setAreaSelection(const SDL2pp::Rect& r)
{
	areaSelection.set(r);
}

void World::generateRoad(int col)
{
	for (int row = 1; row < ROW_COUNT - 1; ++row)
	{
		cells[row][col + 0] = Tiles::RoadSideWalk;
		cells[row][col + 1] = Tiles::RoadLeft;
		cells[row][col + 2] = Tiles::RoadSpace;
		cells[row][col + 3] = (row % 2) ? Tiles::RoadMiddle : Tiles::RoadSpace;
		cells[row][col + 4] = Tiles::RoadSpace;
		cells[row][col + 5] = Tiles::RoadRight;
		cells[row][col + 6] = Tiles::RoadSideWalk;
	}
}

void World::generateBorders()
{
	for (size_t col = 0; col < COL_COUNT; ++col)
	{
		cells[0][col] = Tiles::Border;
		cells[ROW_COUNT - 1][col] = Tiles::Border;
	}

	for (size_t row = 0; row < ROW_COUNT; ++row)
	{
		cells[row][0] = Tiles::Border;
		cells[row][COL_COUNT - 1] = Tiles::Border;
	}
}

void World::createWorker(const Vec2& pos)
{
	Worker* worker = new Worker(renderer, this);
	worker->setPos(pos);
	workers.push_back(worker);
}
