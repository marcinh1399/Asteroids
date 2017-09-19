#pragma once
#include <Box2D\Box2D.h>

class CoreOfAI
{

public:

	friend class AIObject;

	struct Position
	{
		b2Vec2 previous;
		b2Vec2 current;

		Position() = default;

		Position(b2Vec2 position)
		{
			previous = position;
			current = position;
		}

		float squaredDistancePrevious(b2Vec2 object_previous)
		{
			return b2DistanceSquared(previous, object_previous);
		}

		float squaredDistanceCurrent(b2Vec2 object_current)
		{
			return b2DistanceSquared(current, object_current);
		}

		float squaredDistancePrevious(const Position & object)
		{
			return b2DistanceSquared(previous, object.previous);
		}

		float squaredDistanceCurrent(const Position & object)
		{
			return b2DistanceSquared(previous, object.current);
		}

		float deltaSquaredDistance(const Position & object)
		{
			return squaredDistanceCurrent(object) - squaredDistancePrevious(object);
		}
			
		void update(b2Vec2 new_current)
		{
			previous = current;
			current = new_current;
		}

		b2Vec2 deltaPosition()
		{
			return current - previous;
		}
	};

	struct FrontAndRear
	{
		b2Vec2 front;
		b2Vec2 rear;
		b2Vec2 center;

		float angle(b2Vec2 object_center) // maybe in future I'll change something in this function
		{
			b2Vec2 v1 = front - rear;
			b2Vec2 v2 = object_center - center;

			return -b2Abs(atan2(v1.y, v1.x) - atan2(v2.y, v2.x));
		}

		b2Vec2 deltaPosition()
		{
			return front - rear;
		}
	};


private:

public:


	const size_t number_of_rays = 32;
	const size_t ray_max_fraction = 32;
	const size_t ray_max_fraction_shoot = 16;
	const size_t radius_of_observation = 32;
	const size_t radius_squared = radius_of_observation * radius_of_observation;
	const size_t minimal_distance_to_player = 16;


	//Multipliers
	const float escape_from_object = 1.f;
	const float distance_from_object = 1.f;
	const float approaching_to_player = 10000;
	const float rotate_to_player = 30;
	const float rotate_to_direction_of_movement = 10;	
	const float shoot_multiplier = 1000.f;


	float distanceAndApproaching(Position & ai, Position & object);


	float moveToPlayer(FrontAndRear & this_object, Position & ai, Position & player_position);


	float shoot(FrontAndRear & this_object, b2Fixture * fixture);


	float keepRotationToMovementDirection(Position & ai, CoreOfAI::FrontAndRear & this_object);


	bool isInRadius(b2Vec2 this_object, b2Vec2 object);


	float rateRayCast(Position position, b2Fixture * fixture);
};

