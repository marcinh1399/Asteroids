#include "stdafx.h"
#include "CreationManager.h"





bool CreationManager::createObject(const float & delta)
{
	timer += delta;

	if (current_quantity >= max_quantity)
		return false;

	bool create = false;

	if (timer.use() || current_quantity < min_quantity)
		create = (rand() % range_of_rand) >= min_value_of_rand;

	if (create)
		++current_quantity;

	return create;
}

CreationManager::CreationManager()
	: timer(TimeManager(INFINITY, false))
{
}
