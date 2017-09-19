#pragma once
#include "TimeManager.h"
#include <cassert>



class CreationManager
{
public:

	size_t current_quantity;
	size_t min_quantity; // greater chance to make object if current_quantity is less than min_quantity
	size_t max_quantity;


	TimeManager timer;

	size_t range_of_rand;
	size_t min_value_of_rand; // if random value is greater or equal than min_value_of_rand then create the object


	bool createObject(const float & delta);

	CreationManager();

};

