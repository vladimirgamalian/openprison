#pragma once
#include <queue>
#include "WorkerTask.h"

class WorkerTaskQueue
{
public:
	bool pop(WorkerTask& task);
	void push(const WorkerTask& task);

private:
	std::queue<WorkerTask> que;
};
