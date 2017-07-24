#include "stdafx.h"
#include "AsteroidBuilder.h"



void AsteroidBuilder::setRangeOfRadius(const int & max_radius)
{
	min_radius = rnd_radius = max_radius / 2;
}

int AsteroidBuilder::generateShape()
{
	int amount_of_vertices = rand() % rnd_vertices + min_vertices;
	int angle_range = 360 / amount_of_vertices;

	b2_vertices = new b2Vec2[amount_of_vertices];
	sf_vertices = new sf::Vector2f[amount_of_vertices];


	for (int i = 0; i < amount_of_vertices; ++i)
	{
		int length = min_radius + rand() % rnd_radius;
		int angle = rand() % angle_range + i * angle_range;
		float radians = angle * M_PI / 180.f;
		float x = sinf(radians) * length;
		float y = cosf(radians) * length;

		sf_vertices[i] = sf::Vector2f{ x, y };

		#ifndef NDEBUG

		float omega = 0.01f;
		float xxyy = x*x + y*y;
		float max_length = (min_radius + rnd_radius - 1)*(min_radius + rnd_radius - 1) + omega;

		#endif // !NDEBUG

		assert(xxyy <= max_length);

	}

	resizeToB2(amount_of_vertices);

	return amount_of_vertices;
}

void AsteroidBuilder::resizeToB2(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		float x = sf_vertices[i].x * SCALE;
		float y = sf_vertices[i].y * SCALE;
		b2_vertices[i].Set(x, y);
	}
}


AsteroidBuilder::AsteroidBuilder(int max_radius, b2World * ptr_world) : _world(ptr_world)
{
	setRangeOfRadius(max_radius);
	srand(time(NULL));
}

AsteroidBuilder::~AsteroidBuilder()
{
}
