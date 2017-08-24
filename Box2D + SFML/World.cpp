#include "stdafx.h"
#include "World.h"


sf::Vector2f World::asteroidStartingPosition()
{
	constexpr float r2 = (radius + safe_distance) * (radius + safe_distance);
	
	float r = sqrtf(r2);

	float angle = Coords::radians(rand() % 360);
	
	float x = cosf(angle) * r + radius;
	float y = sinf(angle) * r + radius;

	return sf::Vector2f(x, y);
}

sf::Vector2f World::asteroidDestPosition()
{
	constexpr float r2 = (radius - safe_distance) * (radius - safe_distance);

	int r = static_cast<int>(sqrtf(r2));

	float length = rand() % r;

	float angle = Coords::radians(rand() % 360);

	float x = cosf(angle) * length + radius;
	float y = sinf(angle) * length + radius;

	return sf::Vector2f(x, y);
}

bool World::outOfMap(sf::Vector2f v)
{
	constexpr float r2 = (radius + safe_distance) * (radius + safe_distance);

	float length = (radius - v.x) * (radius - v.x) + (radius - v.y) * (radius - v.y);

	return length > r2;
}

bool World::inMap(sf::Vector2f v)
{
	constexpr float r2 = radius * radius;

	float length = (radius - v.x) * (radius - v.x) + (radius - v.y) * (radius - v.y);

	return length < r2;
}

