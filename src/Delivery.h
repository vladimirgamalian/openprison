#pragma once
#include "DeliveryQueue.h"
#include "WorldObject.h"

class Delivery : public WorldObject
{
public:
	Delivery(DeliveryQueue& deliveryQueue);

	virtual void update() override;
	virtual void draw(const Vec2& origin) override;

private:
	DeliveryQueue& deliveryQueue;
};
