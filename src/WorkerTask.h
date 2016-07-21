#pragma once
#include "Vec2.h"

class WorkerTask
{
public:
	WorkerTask() {};
	WorkerTask(int taskType, const Vec2& pos) : taskType(taskType), pos(pos) {}

	struct TaskType
	{
		enum
		{
			BuildWall
		};
	};

	int taskType = 0;
	Vec2 pos;
private:

};
