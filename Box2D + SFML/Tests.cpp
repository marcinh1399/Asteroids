#include "stdafx.h"
#include "Tests.h"


Tests::Tests()
{
}

void Tests::isPointInCirlce(float x, float y, float radius)
{
	float epsilon = 0.01f; // accuracy
	float distance_from_center = x*x + y*y;
	float max_length = radius * radius + epsilon;

	assert(distance_from_center <= max_length);
	
}


Tests::~Tests()
{
}
