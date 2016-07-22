#pragma once
#include "Vec2.h"

class Box;

class WorkerTask
{
public:
	WorkerTask() {};
	WorkerTask(int taskType, const Vec2& pos0)
		: taskType(taskType), pos0(pos0) {}
	WorkerTask(int taskType, const Vec2& pos0, Box* box)
		: taskType(taskType), pos0(pos0), box(box) {}

	struct TaskType
	{
		enum
		{
			BuildWall,
			MoveBox
		};
	};

	int taskType = 0;
	Vec2 pos0;
	Box* box;

private:

};
