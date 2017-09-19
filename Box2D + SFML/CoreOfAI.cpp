#include "stdafx.h"
#include "CoreOfAI.h"




float CoreOfAI::distanceAndApproaching(Position & ai, Position & object)
{
	float rate = escape_from_object * ai.deltaSquaredDistance(object);
	rate += distance_from_object * (radius_squared - ai.squaredDistanceCurrent(object));

	return rate;
}

float CoreOfAI::moveToPlayer(FrontAndRear & this_object, CoreOfAI::Position & ai, CoreOfAI::Position & player_position)
{
	float rate = approaching_to_player * ai.deltaSquaredDistance(player_position);
	rate += rotate_to_player * this_object.angle(player_position.current);

	return rate;
}

float CoreOfAI::shoot(FrontAndRear & this_object, b2Fixture * fixture)
{
	float rate = 0.f;

	b2RayCastInput in;
	in.p1 = this_object.rear;
	in.p2 = this_object.front;
	in.maxFraction = ray_max_fraction_shoot;

	b2RayCastOutput out;

	if (fixture->RayCast(&out, in, 0))
		rate = shoot_multiplier * (in.maxFraction - out.fraction);

	return rate;
}

float CoreOfAI::keepRotationToMovementDirection(Position & ai, CoreOfAI::FrontAndRear & this_object)
{

	auto front = this_object.front;
	auto rear = this_object.rear;
	
	auto prev = ai.previous;
	auto curr = ai.current;

	prev *= 100.f;
	curr *= 100.f;

	float rate_prev = b2DistanceSquared(prev, rear) - b2DistanceSquared(prev, front);
	float rate_curr = b2DistanceSquared(curr, rear) - b2DistanceSquared(curr, front);

	float rate = rotate_to_direction_of_movement * (rate_curr - rate_prev);

	return rate;
}

bool CoreOfAI::isInRadius(b2Vec2 this_object, b2Vec2 object)
{
	float sq_distance = b2DistanceSquared(this_object, object);

	return sq_distance <= radius_squared;
}

float CoreOfAI::rateRayCast(CoreOfAI::Position position, b2Fixture * fixture)
{	
	float rate = 0.f;

	float angle = 360.f / number_of_rays;

	const auto & previous = position.previous;
	const auto & current = position.current;

	b2RayCastInput in;
	in.p1 = current;
	in.maxFraction = ray_max_fraction;

	for (int i = 0; i < number_of_rays; ++i)
	{
		float alpha = angle * i;

		float x = sinf(alpha);
		float y = cosf(alpha);

		in.p2 = current + b2Vec2(x, y);

		b2RayCastOutput out;
		
		float c_rate = 0.f;
		float p_rate = 0.f;

		if (fixture->RayCast(&out, in, 0))
			c_rate = escape_from_object * (in.maxFraction - out.fraction);

		in.p2 = previous + b2Vec2(x, y);

		if (fixture->RayCast(&out, in, 0))
			p_rate = escape_from_object * (in.maxFraction - out.fraction);

		rate += (p_rate - c_rate);
	}

	return rate;
}
