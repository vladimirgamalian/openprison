#pragma once
#include <queue>

class DeliveryQueue
{
public:
	void push(int item);
	bool pop(int& item);

private:
	std::queue<int> que;
};
