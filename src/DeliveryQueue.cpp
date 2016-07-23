#include "DeliveryQueue.h"

void DeliveryQueue::push(int item)
{
	que.push(item);
}

bool DeliveryQueue::pop(int& item)
{
	if (que.empty())
		return false;
	item = que.front();
	que.pop();
	return true;
}
