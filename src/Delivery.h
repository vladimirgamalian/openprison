#pragma once
#include "DeliveryQueue.h"

class Delivery
{
public:
	Delivery(DeliveryQueue& deliveryQueue);

private:
	DeliveryQueue& deliveryQueue;
};
