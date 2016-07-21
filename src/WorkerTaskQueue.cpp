#include "WorkerTaskQueue.h"

bool WorkerTaskQueue::pop(WorkerTask& task)
{
	if (que.empty())
		return false;
	task = que.front();
	que.pop();
	return true;
}

void WorkerTaskQueue::push(const WorkerTask& task)
{
	que.push(task);
}
